#ifndef STANDALONE_PASSES_H
#define STANDALONE_PASSES_H
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Support/LLVM.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"
#include "mlir/Dialect/StandardOps/IR/Ops.h"
#include "Standalone/StandaloneOps.h"
#include <memory>
#include <string>


namespace mlir{
namespace standalone {
    


// class FuncOp;
void registerToConstantPass();
/// Generate the code for registering passes.
}
} // end namespace mlir

#endif // STANDALONE_PASSES_H

