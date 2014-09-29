// Experimental type annotation support for Clang.
// By Adrian Sampson <asampson@cs.washington.edu>.

#include "CodeGenModule.h"
#include "llvm/IR/Constants.h"
/*
#include "llvm/IR/Metadata.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Instruction.h"
*/

using namespace clang;
using namespace clang::CodeGen;

void CodeGenModule::TADecorate(llvm::Instruction *Inst, clang::QualType Ty) {
  llvm::LLVMContext &Ctx = getLLVMContext();
  // TODO record the actual annotation.
  // TODO record the "depth" of the annotation in the reference type chain.
  llvm::Value *Args[2] = {
    llvm::MDString::get(Ctx, "XXX"),
    llvm::ConstantInt::get(llvm::Type::getInt8Ty(Ctx), 0, false)
  };
  llvm::MDNode *node = llvm::MDNode::get(Ctx, Args);
  Inst->setMetadata("tyann", node);
}
