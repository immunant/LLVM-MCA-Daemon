set(LLVM_HAVE_LINK_VERSION_SCRIPT 1)
find_package (Python3 REQUIRED
  COMPONENTS Interpreter Development)

set(LLVM_EXPORTED_SYMBOL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Broker.exports)

add_llvm_library(VivisectBroker SHARED
  Broker.cpp

  LINK_COMPONENTS
  Object
  )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

unset(LLVM_EXPORTED_SYMBOL_FILE)
