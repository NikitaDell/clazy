/*
  This file is part of the clazy static checker.

    SPDX-FileCopyrightText: 2017 Sergio Martins <smartins@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef CLAZY_STRICT_ITERATORS_H
#define CLAZY_STRICT_ITERATORS_H

#include "checkbase.h"

#include <string>

class ClazyContext;

namespace clang
{
class CXXConstructExpr;
class ImplicitCastExpr;
class CXXOperatorCallExpr;
class Stmt;
}

/**
 * See README-strict-iterators.md for more info.
 */
class StrictIterators : public CheckBase
{
public:
    explicit StrictIterators(const std::string &name, ClazyContext *context);
    void VisitStmt(clang::Stmt *stmt) override;

private:
    bool handleImplicitCast(clang::ImplicitCastExpr *);
    bool handleOperator(clang::CXXOperatorCallExpr *);
};

#endif
