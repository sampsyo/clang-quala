// Experimental type annotation support for Clang.
// By Adrian Sampson <asampson@cs.washington.edu>.

#include "CodeGenModule.h"
#include "llvm/IR/Constants.h"

using namespace clang;
using namespace clang::CodeGen;

void CodeGenModule::TADecorate(llvm::Instruction *Inst, clang::QualType Ty) {
  llvm::LLVMContext &Ctx = getLLVMContext();

  // Is this an annotated type?
  // TODO Try desugaring.
  if (auto *AT = llvm::dyn_cast<AnnotatedType>(Ty)) {
    StringRef Ann = AT->getAnnotation();

    // TODO record the "depth" of the annotation in the reference type chain.
    llvm::Value *Args[2] = {
      llvm::MDString::get(Ctx, Ann),
      llvm::ConstantInt::get(llvm::Type::getInt8Ty(Ctx), 0, false)
    };

    llvm::MDNode *node = llvm::MDNode::get(Ctx, Args);
    Inst->setMetadata("tyann", node);
  }
}

void CodeGenModule::TADecorate(llvm::Value *V, clang::QualType Ty) {
  if (auto *Inst = dyn_cast<llvm::Instruction>(V)) {
    TADecorate(Inst, Ty);
  } else {
    // TODO maybe handle this case
  }
}
