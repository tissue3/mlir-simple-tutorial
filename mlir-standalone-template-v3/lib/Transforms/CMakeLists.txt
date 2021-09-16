add_mlir_dialect_library(StandaloneTransforms
  ToConstant.cpp
  
  ADDITIONAL_HEADER_DIRS
  ${PROJECT_SOURCE_DIR}/include/Standalone


  DEPENDS
  MLIRStandaloneOpsIncGen

  LINK_LIBS PUBLIC
  MLIRIR
  MLIRPass
)
