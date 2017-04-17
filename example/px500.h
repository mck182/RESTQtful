/*  This file is part of RESTQtful
    Copyright (C) 2017  Martin Klapetek <mklapetek@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License version 2.1, as published by the Free Software Foundation.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef PX500_H
#define PX500_H

#include <serverbase.h>
#include "px500secrets.h"

class Px500 : public ServerBase
{
    Q_OBJECT

public:
    Px500(QObject *parent = 0);
    virtual const QString serverBaseUrl() const;
    virtual const Parameters requestHeaders() const;

    void photos(OnCompleted onCompleted);

    void photoComments(int id, OnCompleted onCompleted);
};

#endif // PX500_H
