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

#ifndef SERVERBASE_H
#define SERVERBASE_H

#include <QObject>
#include <QJsonDocument>
#include <QHash>

class QNetworkReply;
class QNetworkRequest;
class QNetworkAccessManager;

typedef QHash<QString, QString> Parameters;
typedef std::function<void(const QJsonDocument &json, int statusCode)> OnCompleted;

class ServerBase : public QObject
{
    Q_OBJECT
public:
    explicit ServerBase(QObject *parent = 0);

    virtual const QString serverBaseUrl() const = 0;
    virtual const QHash<QString, QString> requestHeaders() const = 0;

    // -- GET --------------------------------------------
    QNetworkReply* get(const QString &path,
                       const Parameters &params,
                       const Parameters &headers = Parameters()) const;

    void get(const QString &path,
             const Parameters &params,
             const Parameters &headers,
             OnCompleted onCompleted) const;

    // -- POST -------------------------------------------
    QNetworkReply* post(const QString &path,
                        const QJsonDocument &body,
                        const Parameters &params,
                        const Parameters &headers = Parameters()) const;

    void post(const QString &path,
              const QJsonDocument &body,
              const Parameters &params,
              const Parameters &headers,
              OnCompleted onCompleted) const;

private:
    QNetworkRequest constructRequest(const QString &path,
                                     const Parameters &params,
                                     const Parameters &headers) const;

    void handleNetworkReply(QNetworkReply *reply, OnCompleted onCompleted) const;
};

#endif // SERVERBASE_H
