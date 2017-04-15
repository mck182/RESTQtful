#include <QCoreApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "qobjecthelper.h"
#include "example/pxphoto.h"
#include "example/px500.h"

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

    });

    return a.exec();
}
