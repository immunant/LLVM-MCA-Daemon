#include "BrokerFacade.h"
#include "Brokers/Broker.h"
#include "Brokers/BrokerPlugin.h"

#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/SubtargetFeature.h"
#include "llvm/MC/MCDisassembler/MCDisassembler.h"
#include "llvm/MCA/MetadataCategories.h"
#include "llvm/MCA/MetadataRegistry.h"
#include "llvm/MCA/HardwareUnits/LSUnit.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"

#include <string>
#include <thread>

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

using namespace llvm;
using namespace mcad;

namespace {
class GenericBroker : public Broker {

  std::string ListenAddr;
  int ServSocketFD;

  const Target &TheTarget;
  MCContext &Ctx;
  const MCSubtargetInfo &STI;
  std::unique_ptr<MCDisassembler> DisAsm;

  std::unique_ptr<std::thread> ReceiverThread;

  int fetch(MutableArrayRef<const MCInst *> MCIS, int Size = -1,
            Optional<MDExchanger> MDE = llvm::None) override;

public:
  GenericBroker(StringRef ListenAddress, const MCSubtargetInfo &MSTI,
                 MCContext &C, const Target &T);
  void initializeServer();
  void initializeUnixServer();
  void initializeDisassembler();
  void recvWorker();
};
} // end anonymous namespace

GenericBroker::GenericBroker(StringRef ListenAddress,
                               const MCSubtargetInfo &MSTI, MCContext &C,
                               const Target &T)
    : ListenAddr(ListenAddress.str()), ServSocketFD(-1), TheTarget(T), Ctx(C), STI(MSTI) {

      initializeDisassembler();

      initializeUnixServer();

      ReceiverThread =
          std::make_unique<std::thread>(&GenericBroker::recvWorker, this);
}

void GenericBroker::initializeDisassembler() {
  DisAsm.reset(TheTarget.createMCDisassembler(STI, Ctx));
}

void GenericBroker::initializeUnixServer() {
  if ((ServSocketFD = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    errs() << "Error creating socket: " << std::strerror(errno) << "\n";
    exit(1);
  }

  unlink(ListenAddr.c_str());

  sockaddr_un Addr;
  Addr.sun_family = AF_UNIX;
  strcpy(Addr.sun_path, ListenAddr.c_str());

  if (bind(ServSocketFD, (sockaddr *)&Addr, sizeof(Addr)) < 0) {
    errs() << "Error on binding: " << std::strerror(errno) << "\n";
    exit(1);
  }
}

static constexpr unsigned RECV_BUFFER_SIZE = 1024;

void GenericBroker::recvWorker() {
  assert(ServSocketFD >= 0);

  static constexpr int ConnectionQueueLen = 1;
  listen(ServSocketFD, ConnectionQueueLen);
  outs() << "Listening on " << ListenAddr << "...\n";

  int ClientSocketFd;
  uint8_t RecvBuffer[RECV_BUFFER_SIZE];
  SmallVector<uint8_t, RECV_BUFFER_SIZE> MsgBuffer;
  while ((ClientSocketFd = accept(ServSocketFD, nullptr, nullptr))) {
      if (ClientSocketFd < 0) {
          ::perror("Failed to accept client\n");
          continue;
      }
      //LLVM_DEBUG(dbgs() < "Got a new client\n");

      while (true) {
          MsgBuffer.clear();

          size_t ReadLen = read(ClientSocketFd, RecvBuffer, sizeof(TotalMsgSize)); 
          if (!ReadLen) {
              break;
          }
          if (ReadLen < sizeof(TotalMsgSize)) {
              if (ReadLen < 0) {
                  ::perror("Failed to read prefixed size");
              } else {
                  //errs() << "Failed to read entire message
              }
          }
      }
  }
}

int GenericBroker::fetch(MutableArrayRef<const MCInst *> MCIS, int Size,
                          Optional<MDExchanger> MDE) {
  return 0;
}

extern "C" ::llvm::mcad::BrokerPluginLibraryInfo LLVM_ATTRIBUTE_WEAK
mcadGetBrokerPluginInfo() {
  return {LLVM_MCAD_BROKER_PLUGIN_API_VERSION, "GenericBroker", "v0.1",
          [](int argc, const char *const *argv, BrokerFacade &BF) {
            StringRef ListenAddress;
            for (int i = 0; i < argc; ++i) {
              StringRef Arg(argv[i]);

              if (Arg.startswith("-host=")) {
                ListenAddress = Arg.split('=').second;
              }
            }
            if (ListenAddress.empty()) {
                ::exit(1);
            }
            BF.setBroker(std::make_unique<GenericBroker>(
                ListenAddress, BF.getSTI(), BF.getCtx(), BF.getTarget()));
          }};
}
