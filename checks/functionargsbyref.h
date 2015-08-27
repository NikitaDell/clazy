/*
   This file is part of the clang-lazy static checker.

  Copyright (C) 2015 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  Copyright (C) 2015 Sergio Martins <smartins@kde.org>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

  As a special exception, permission is given to link this program
  with any edition of Qt, and distribute the resulting executable,
  without including the source code for Qt in the source distribution.
*/

#ifndef FUNCTION_ARGS_BY_REF_H
#define FUNCTION_ARGS_BY_REF_H

#include "checkbase.h"

namespace clang {
class Decl;
}

/**
 * Finds functions where big non-trivial types are passed by value instead of const-ref.
 * Looks into the body of the functions to see if the argument are read-only, it doesn't emit a warning otherwise.
 */
class FunctionArgsByRef : public CheckBase
{
public:
    FunctionArgsByRef(const std::string &name);
    void VisitDecl(clang::Decl *decl) override;
protected:
    std::vector<std::string> filesToIgnore() const override;
};

#endif
