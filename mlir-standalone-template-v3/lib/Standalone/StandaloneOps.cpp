//===- StandaloneOps.cpp - Standalone dialect ops ---------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Standalone/StandaloneOps.h"
#include "Standalone/StandaloneDialect.h"
#include "mlir/IR/OpImplementation.h"

namespace mlir {
namespace standalone {
void AttrOp::build(Builder builder, OperationState &result, int64_t attr) {

	result.addAttribute("attr", builder.getI32IntegerAttr(attr));
	auto i32Type = IntegerType::get(32, builder.getContext());
	result.types.push_back(i32Type);
}


#define GET_OP_CLASSES
#include "Standalone/StandaloneOps.cpp.inc"
} // namespace standalone
} // namespace mlir
