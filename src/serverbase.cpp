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

#include "networkmanager.h"
#include "serverbase.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

#include <QDebug>

ServerBase::ServerBase(QObject *parent)
    : QObject(parent)
{

}

QNetworkReply *ServerBase::get(const QString &path, const Parameters &params, const Parameters &headers) const
{
    QNetworkRequest request = constructRequest(path, params, headers);
    return NetworkManager::instance()->get(request);
}

void ServerBase::get(const QString &path,
                     const Parameters &params,
                     const Parameters &headers,
                     OnCompleted onCompleted) const
{
    QNetworkRequest request = constructRequest(path, params, headers);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    QNetworkReply *reply = NetworkManager::instance()->get(request);

    handleNetworkReply(reply, onCompleted);
}

QNetworkReply *ServerBase::post(const QString &path,
                                const QJsonDocument &body,
                                const Parameters &params,
                                const Parameters &headers) const
{
    QNetworkRequest request = constructRequest(path, params, headers);
    return NetworkManager::instance()->post(request, body.toJson());
}

void ServerBase::post(const QString &path,
                      const QJsonDocument &body,
                      const Parameters &params,
                      const Parameters &headers,
                      OnCompleted onCompleted) const
{
    QNetworkRequest request = constructRequest(path, params, headers);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = NetworkManager::instance()->post(request, body.toJson());

    handleNetworkReply(reply, onCompleted);
}

QNetworkRequest ServerBase::constructRequest(const QString &path,
                                             const Parameters &params,
                                             const Parameters &headers) const
{
    const QString serverUrl = serverBaseUrl();

    QRegularExpression customParamsMatcher(":(\\w+)/?");
    QRegularExpressionMatchIterator i = customParamsMatcher.globalMatch(path);

    QString adjustedPath = path;
    Parameters nonConstParams = params;

    // Replace all :param in the path with actual data
    // from the params hash
    int cumulatedOffset = 0;
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        const QString matchedParam = match.captured(1);
        const QString param = nonConstParams.take(matchedParam);

        if (!param.isEmpty()) {
            adjustedPath.replace(match.capturedStart() + cumulatedOffset, match.capturedLength(1) + 1, param);
            cumulatedOffset += param.length() - match.capturedLength() + 1;
        }
    }

    QUrl requestUrl(serverUrl + adjustedPath);
    QUrlQuery query;

    // Set the remaining params as URL query items
    for (auto i = nonConstParams.constBegin(); i != nonConstParams.constEnd(); ++i) {
        query.addQueryItem(i.key(), i.value());
    }

    requestUrl.setQuery(query);

    qDebug() << "Request URL" << requestUrl;

    QNetworkRequest request(requestUrl);

    // Set all the headers
    const Parameters finalHeaders = Parameters(headers).unite(requestHeaders());
    for (auto i = finalHeaders.constBegin(); i != finalHeaders.constEnd(); ++i) {
        request.setRawHeader(i.key().toUtf8(), i.value().toUtf8());
    }

    return request;
}

void ServerBase::handleNetworkReply(QNetworkReply *reply, OnCompleted onCompleted) const
{
    connect(reply, &QNetworkReply::finished, [=]() {
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        const QByteArray replyData = reply->readAll();
        const QJsonDocument json = QJsonDocument::fromJson(replyData);
        onCompleted(json, statusCode);

        reply->deleteLater();
    });
}
