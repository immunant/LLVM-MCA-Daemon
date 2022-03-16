#include "BrokerFacade.h"
#include "Brokers/Broker.h"
#include "Brokers/BrokerPlugin.h"

using namespace llvm;
using namespace mcad;

namespace {
class VivisectBroker : public Broker {
    int fetch(MutableArrayRef<const MCInst*> MCIS, int Size = -1,
              Optional<MDExchanger> MDE = llvm::None) override;
};
}

int VivisectBroker::fetch(MutableArrayRef<const MCInst*> MCIS, int Size,
                          Optional<MDExchanger> MDE) {
  return 0;
}

extern "C" ::llvm::mcad::BrokerPluginLibraryInfo LLVM_ATTRIBUTE_WEAK
mcadGetBrokerPluginInfo() {
  return {
    LLVM_MCAD_BROKER_PLUGIN_API_VERSION, "VivisectBroker", "v0.1",
    [](int argc, const char *const *argv, BrokerFacade &BF) {
      BF.setBroker(std::make_unique<VivisectBroker>());
    }
  };
}
