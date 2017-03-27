#include <QCoreApplication>
#include <QDebug>
#include <QJsonDocument>

#include "example/px500.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Px500 *pxServer = new Px500(&a);

    pxServer->photos([pxServer](const QJsonDocument &json, int statusCode) {
        qDebug() << "Photo GET return status:" << statusCode;
        qDebug() << json;
        qDebug();

        pxServer->photoComments(198209741, [](const QJsonDocument &json, int statusCode) {
            qDebug() << "Comments for the photo:" << json;
        });
    });

    return a.exec();
}
