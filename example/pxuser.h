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

#ifndef PXUSER_H
#define PXUSER_H

#include <QObject>
#include <QUrl>

class PxUser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(QString username READ username WRITE setUsername)
    Q_PROPERTY(QString firstname READ firstname WRITE setFirstname)
    Q_PROPERTY(QString lastname READ lastname WRITE setLastname)
    Q_PROPERTY(QString city READ city WRITE setCity)
    Q_PROPERTY(QString country READ country WRITE setCountry)
    Q_PROPERTY(QString fullname READ fullname WRITE setFullname)
    Q_PROPERTY(QUrl userpicUrl READ userpicUrl WRITE setUserpicUrl)
    Q_PROPERTY(int upgradeStatus READ upgradeStatus WRITE setUpgradeStatus)

public:
    Q_INVOKABLE explicit PxUser(QObject *parent = 0);

    int id() const { return m_id; }
    QString username() const { return m_username; }
    QString firstname() const { return m_firstname; }
    QString lastname() const { return m_lastname; }
    QString city() const { return m_city; }
    QString country() const { return m_country; }
    QString fullname() const { return m_fullname; }
    QUrl userpicUrl() const { return m_userpicUrl; }
    int upgradeStatus() const { return m_upgradeStatus; }

public slots:
    void setId(int id) { m_id = id; }
    void setUsername(QString username) { m_username = username; }
    void setFirstname(QString firstname) { m_firstname = firstname; }
    void setLastname(QString lastname) { m_lastname = lastname; }
    void setCity(QString city) { m_city = city; }
    void setCountry(QString country) { m_country = country; }
    void setFullname(QString fullname) { m_fullname = fullname; }
    void setUserpicUrl(QUrl userpicUrl) { m_userpicUrl = userpicUrl; }
    void setUpgradeStatus(int upgradeStatus) { m_upgradeStatus = upgradeStatus; }

private:
    int m_id;
    QString m_username;
    QString m_firstname;
    QString m_lastname;
    QString m_city;
    QString m_country;
    QString m_fullname;
    QUrl m_userpicUrl;
    int m_upgradeStatus;
};

Q_DECLARE_METATYPE(PxUser*)

#endif // PXUSER_H
