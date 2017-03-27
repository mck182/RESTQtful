#ifndef PX500_H
#define PX500_H

#include "serverbase.h"
#include "px500secrets.h"

class Px500 : public ServerBase
{
    Q_OBJECT

public:
    Px500(QObject *parent = 0);
    virtual const QString serverBaseUrl() const;
    virtual const Parameters requestHeaders() const;

    void photos(OnCompleted onCompleted);

    void photoComments(int id, OnCompleted onCompleted);
};

#endif // PX500_H
