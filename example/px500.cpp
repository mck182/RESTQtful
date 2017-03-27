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
        { "rpp", "1" },
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
