
#include "Standalone/StandaloneDialect.h"
#include "Standalone/StandaloneOps.h"
#include "Standalone/StandalonePasses.h"
#include "EDSC/Intrinsics.h"

#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "mlir/Dialect/StandardOps/IR/Ops.h"
#include "mlir/Transforms/DialectConversion.h"

#include "mlir/IR/Builders.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/Dialect/StandardOps/IR/Ops.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/LoopUtils.h"
#include "mlir/Transforms/Passes.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/Utils.h"


#define DEBUG_TYPE "to-constant"
using namespace mlir;

namespace {

    struct AttrOpConversion : public OpRewritePattern<standalone::FooOp>
    {
        using OpRewritePattern<standalone::FooOp>::OpRewritePattern;
        AttrOpConversion(MLIRContext *context) : OpRewritePattern<standalone::FooOp>(context){}

        LogicalResult matchAndRewrite(standalone::FooOp op,
                                      PatternRewriter &rewriter) const override
        {

            auto const_op = cast<mlir::ConstantOp>(op.getOperand().getDefiningOp());
            int64_t n = const_op.getValue().cast<IntegerAttr>().getInt();
            //get value of constant op

            
            auto loc = op.getLoc();

            Value attrOp = rewriter.create<mlir::standalone::AttrOp>(loc, n);
            rewriter.replaceOp(op, attrOp);

            

            return success();        
        }
    };



struct ToConstant : public PassWrapper<ToConstant, FunctionPass>  {

  void runOnFunction() override;

};

} // end anonymous namespace



void ToConstant::runOnFunction() {
  OwningRewritePatternList patterns;
  patterns.insert<AttrOpConversion>(&getContext());
  ConversionTarget target(getContext());
  target.addLegalDialect<mlir::StandardOpsDialect>();
  target.addLegalOp<mlir::standalone::AttrOp>();
  if (failed(applyPartialConversion(getFunction(), target, std::move(patterns) ) ) ){
    signalPassFailure();
  }

}


void standalone::registerToConstantPass() {
    PassRegistration<ToConstant>(
      "to-constant",
      "...");
}
