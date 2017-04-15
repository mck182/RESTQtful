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

#include "px500.h"

Px500::Px500(QObject *parent)
    : ServerBase(parent)
{

}

const QString Px500::serverBaseUrl() const
{
    return QStringLiteral("https://api.500px.com/v1");
}

const Parameters Px500::requestHeaders() const
{
    const QHash<QString, QString> headers = QHash<QString, QString> {
        // {"Authorization", "Bearer " + PX500_OAUTH_TOKEN}
    };

    return headers;
}

void Px500::photos(OnCompleted onCompleted)
{
    const Parameters params = Parameters {
        { "rpp", "10" },
        { "consumer_key", PX500_CONSUMER_KEY }
    };

    get(QStringLiteral("/photos"), params, Parameters(), onCompleted);
}

void Px500::photoComments(int id, OnCompleted onCompleted)
{
    const Parameters params = Parameters {
        { "consumer_key", PX500_CONSUMER_KEY },
        { "id", QString::number(id) }
    };

    get(QStringLiteral("/photos/:id/comments"), params, Parameters(), onCompleted);
}
