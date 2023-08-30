/*
    This file is part of the clazy static checker.

    SPDX-FileCopyrightText: 2015 Klarälvdalens Datakonsult AB a KDAB Group company info@kdab.com
    Author: Sérgio Martins <sergio.martins@kdab.com>

    SPDX-FileCopyrightText: 2015 Sergio Martins <smartins@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef CLANG_LAZY_QGETENV_H
#define CLANG_LAZY_QGETENV_H

#include "checkbase.h"

#include <string>

class ClazyContext;

namespace clang
{
class Stmt;
}

/**
 * Finds inefficient usages of qgetenv
 *
 * See README-qgetenv for more information
 */
class QGetEnv : public CheckBase
{
public:
    explicit QGetEnv(const std::string &name, ClazyContext *context);
    void VisitStmt(clang::Stmt *stmt) override;
};

#endif
