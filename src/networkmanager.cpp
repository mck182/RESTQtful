#include "networkmanager.h"

#include <QNetworkAccessManager>

Q_GLOBAL_STATIC(NetworkManager, sharedInstance)

NetworkManager::NetworkManager()
    : QNetworkAccessManager()

{

}

NetworkManager *NetworkManager::instance()
{
    return sharedInstance;
}
