/*
    This file is part of the clazy static checker.

    SPDX-FileCopyrightText: 2015 Klarälvdalens Datakonsult AB a KDAB Group company info@kdab.com
    Author: Sérgio Martins <sergio.martins@kdab.com>

    SPDX-FileCopyrightText: 2015 Sergio Martins <smartins@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef CLANG_LAZY_IMPLICIT_CASTS_H
#define CLANG_LAZY_IMPLICIT_CASTS_H

#include "checkbase.h"

#include <string>

class ClazyContext;

namespace clang
{
class ImplicitCastExpr;
class SourceLocation;
class Stmt;
class CallExpr;
class FunctionDecl;
}

/**
 * Finds places with unwanted implicit casts.
 *
 * See README-implicit-casts for more information
 */
class ImplicitCasts : public CheckBase
{
public:
    ImplicitCasts(const std::string &name, ClazyContext *context);
    void VisitStmt(clang::Stmt *stmt) override;

private:
    bool isBoolToInt(clang::FunctionDecl *func) const;
    bool isMacroToIgnore(clang::SourceLocation loc) const;
};

#endif
