#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QNetworkAccessManager>

class NetworkManager : public QNetworkAccessManager
{
public:
    explicit NetworkManager();
    static NetworkManager* instance();
};

#endif // NETWORKMANAGER_H
