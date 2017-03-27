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
