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

#include <QCoreApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "qobjecthelper.h"
#include "pxphoto.h"
#include "px500.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Px500 *pxServer = new Px500(&a);

    qRegisterMetaType<PxPhoto*>("PxPhoto*");
    qRegisterMetaType<PxUser*>("PxUser*");

    pxServer->photos([pxServer](const QJsonDocument &json, int statusCode) {
        qDebug() << "Photo GET return status:" << statusCode;
        qDebug();
        auto photosArray = json.object().value(QStringLiteral("photos"));

        Q_FOREACH (const QJsonValue &jsonPhoto, photosArray.toArray()) {
            PxPhoto *photo = new PxPhoto();
            QObjectHelper::qjsonobject2qobject(jsonPhoto.toObject(), photo);

            qDebug() << photo->id() << photo->name() << photo->user()->fullname();
        }


//        pxServer->photoComments(198209741, [](const QJsonDocument &json, int statusCode) {
//            qDebug() << "Comments for the photo:" << json;
//        });
    });

    return a.exec();
}
