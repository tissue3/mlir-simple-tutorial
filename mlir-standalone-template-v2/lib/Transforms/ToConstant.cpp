
#include "Standalone/StandaloneDialect.h"
#include "Standalone/StandaloneOps.h"
#include "Standalone/StandalonePasses.h"
#include "EDSC/Intrinsics.h"



#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "mlir/Dialect/StandardOps/IR/Ops.h"
#include "mlir/Dialect/SCF/EDSC/Builders.h"
#include "mlir/Transforms/DialectConversion.h"

#include "mlir/IR/AffineExpr.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/IntegerSet.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Module.h"
#include "mlir/IR/StandardTypes.h"
#include "mlir/IR/Verifier.h"
#include "mlir/IR/Types.h"
#include "mlir/IR/Visitors.h"
#include "mlir/IR/BlockSupport.h"
#include "mlir/Dialect/StandardOps/IR/Ops.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/LoopUtils.h"
#include "mlir/Transforms/Passes.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/Utils.h"

#include "mlir/Dialect/Affine/EDSC/Intrinsics.h"
#include "mlir/Dialect/Linalg/EDSC/Builders.h"
#include "mlir/Dialect/Linalg/EDSC/Intrinsics.h"
#include "mlir/Dialect/SCF/EDSC/Intrinsics.h"
#include "mlir/Dialect/StandardOps/EDSC/Intrinsics.h"
#include "mlir/Dialect/Vector/EDSC/Intrinsics.h"
#include "mlir/Analysis/Liveness.h"

#define DEBUG_TYPE "to-constant"
using namespace mlir;

namespace {


struct ToConstant : public PassWrapper<ToConstant, FunctionPass>  {

  void runOnFunction() override;

};

} // end anonymous namespace


void ToConstant::runOnFunction() {
  auto f = getFunction();//top function
  MLIRContext *context = &getContext();
  OpBuilder builder(context);
  ScopedContext scope(builder, f.getLoc());

  for (auto op: f.getRegion().getOps<standalone::FooOp>()){
    llvm::outs()<<op<<"\n";
    builder.setInsertionPoint(op);//foo(%0), %0 = constant
    
    auto const_op = cast<mlir::ConstantOp>(op.getOperand().getDefiningOp());
    //https://github.com/llvm/llvm-project/blob/master/mlir/include/mlir/Dialect/StandardOps/IR/Ops.td#L1395
    int64_t n = const_op.getValue().cast<IntegerAttr>().getInt();//const
    
    llvm::outs()<<n<<"\n";
    //Value res = builder.create<standalone::readattr>(builder.getLoc(), n);
    Value res = attr_op(n);
    op.erase();
  }


}


void standalone::registerToConstantPass() {
    PassRegistration<ToConstant>(
      "to-constant",
      "...");
}
