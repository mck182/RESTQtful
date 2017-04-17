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

#ifndef PXPHOTO_H
#define PXPHOTO_H

#include <QObject>

#include "pxuser.h"
#include "qobjecthelper.h"

class PxPhoto : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(int timesViewed READ timesViewed WRITE setTimesViewed)
    Q_PROPERTY(PxUser* user READ user WRITE setUser)
    Q_PROPERTY(QString highestRatingDate READ highestRatingDate WRITE setHighestRatingDate)

    Q_PROPERTY(int jsonDelimiter READ jsonDelimiter)

public:
    Q_INVOKABLE explicit PxPhoto(QObject *parent = 0);

    int id() const { return m_id; }
    QString name() const { return m_name; }
    QString description() const { return m_description; }
    int timesViewed() const { return m_timesViewed; }
    PxUser* user() const { return m_user; }
    QString highestRatingDate() const { return m_highestRatingDate; }

    QObjectHelper::JsonDelimiter jsonDelimiter() const { return QObjectHelper::Underscore; }

public slots:
    void setId(int id) { m_id = id; }
    void setName(const QString &name) { m_name = name; }
    void setDescription(const QString &description) { m_description = description; }
    void setTimesViewed(int timesViewed) { m_timesViewed = timesViewed; }
    void setUser(PxUser *user) { m_user = user; }
    void setHighestRatingDate(const QString &highestRatingDate) { m_highestRatingDate = highestRatingDate; }

private:
    int m_id;
    QString m_name;
    QString m_description;
    int m_timesViewed;
    PxUser *m_user;
    QString m_highestRatingDate;
};

Q_DECLARE_METATYPE(PxPhoto*)

#endif // PXPHOTO_H
