/*
 * Copyright (c) 2021-present, Trail of Bits, Inc.
 * All rights reserved.
 *
 * This source code is licensed in accordance with the terms specified in
 * the LICENSE file found in the root directory of this source tree.
 */

#pragma once

#include <clang/Tooling/Tooling.h>
#include <doctest/doctest.h>

std::unique_ptr<clang::ASTUnit> GetASTUnit(const char *code = "");

template <typename T>
T *GetDecl(clang::DeclContext *decl_ctx, const std::string &name) {
  auto &ctx{decl_ctx->getParentASTContext()};
  auto lookup_result{decl_ctx->noload_lookup(&ctx.Idents.get(name))};
  REQUIRE(lookup_result.end() - lookup_result.begin() == 1);
  auto decl{clang::dyn_cast<T>(lookup_result.front())};
  REQUIRE(decl != nullptr);
  return decl;
}