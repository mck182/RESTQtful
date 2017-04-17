/* This file is part of qjson
  *
  * Copyright (C) 2009 Till Adam <adam@kde.org>
  * Copyright (C) 2009 Flavio Castelli <flavio@castelli.name>
  * Copyright (C) 2016 Anton Kudryavtsev <a.kudryavtsev@netris.ru>
  * Copyright (C) 2017 Martin Klapetek <mklapetek@kde.org>
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License version 2.1, as published by the Free Software Foundation.
  *
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public License
  * along with this library; see the file COPYING.LIB.  If not, write to
  * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  * Boston, MA 02110-1301, USA.
  */


#include "qobjecthelper.h"

#include <QMetaObject>
#include <QMetaProperty>
#include <QObject>
#include <QJsonObject>
#include <QString>
#include <QRegularExpression>

#include <QDebug>

QVariantMap QObjectHelper::qobject2qvariant(const QObject *object,
                                            const QStringList &ignoredProperties)
{
    QVariantMap result;

    if (object == Q_NULLPTR) {
        return result;
    }

    const QMetaObject *metaobject = object->metaObject();
    int count = metaobject->propertyCount();

    JsonDelimiter jsonDelimiter = (JsonDelimiter)object->property("jsonDelimiter").toInt();

    for (int i = 0; i < count; ++i) {
        QMetaProperty metaproperty = metaobject->property(i);
        const char *name = metaproperty.name();

        if (!metaproperty.isReadable() || ignoredProperties.contains(QLatin1String(name)))
            continue;

        QVariant value;

        if (metaproperty.type() == QVariant::UserType) {
            QVariant propertyObject = object->property(name);
            QObject *subObject = qvariant_cast<QObject*>(propertyObject);
            if (subObject == Q_NULLPTR) {
                qWarning() << "Unable to extract" << propertyObject.typeName() << "from QVariant,"
                           << "did you register it using qRegisterMetaType<T>(..)?";
            } else {
                value = qobject2qvariant(subObject);
            }
        } else {
           value = object->property(name);
        }

        QString jsonKey;

        if (jsonDelimiter == QObjectHelper::Underscore) {
            jsonKey = QString(name).replace(QRegularExpression("([A-Z])"), "_\\1").toLower();
        } else {
            jsonKey = name;
        }
        result[jsonKey] = value;
    }

    return result;
}

QJsonObject QObjectHelper::qobject2qjsonobject(const QObject *object, const QStringList &ignoredProperties)
{
    const QVariantMap jsonMap = QObjectHelper::qobject2qvariant(object, ignoredProperties);
    return QJsonObject::fromVariantMap(jsonMap);
}

void QObjectHelper::qvariant2qobject(const QVariantMap &variant, QObject *object)
{
    if (object == Q_NULLPTR) {
        return;
    }

    const QMetaObject *metaObject = object->metaObject();
    JsonDelimiter jsonDelimiter = (JsonDelimiter)object->property("jsonDelimiter").toInt();

    for (QVariantMap::const_iterator iter = variant.constBegin(),
        end = variant.constEnd(); iter != end; ++iter) {

        QString propertyName;

        if (jsonDelimiter == QObjectHelper::Underscore) {
            auto parts = iter.key().split('_');
            for (int i = 1; i < parts.size(); i++) {
                parts[i].replace(0, 1, parts[i][0].toUpper());
            }
            propertyName = parts.join("");
        } else {
            propertyName = iter.key();
        }

        int propertyIndex = metaObject->indexOfProperty(propertyName.toLatin1());
        if (propertyIndex < 0)
            continue;

        QMetaProperty metaProperty = metaObject->property(propertyIndex);
        QVariant::Type type = metaProperty.type();
        QVariant value(iter.value());

        if (type == QVariant::Invalid) {
            qWarning() << "The type" << type << "is unknwon, did you register it with"
                       << "Q_DECLARE_METATYPE and qRegisterMetaType<>()?";
        }

        if (type == QVariant::UserType && iter.value().type() == QVariant::Map) {
            const int metaType = QMetaType::type(metaProperty.typeName());

            if (metaType != QMetaType::UnknownType) {
                const QMetaObject *innerMetaObject = QMetaType::metaObjectForType(metaType);
                if (innerMetaObject) {
                    // TODO: Should this sub-object be parented to the `object`?
                    QObject *objectPtr = innerMetaObject->newInstance(Q_ARG(QObject*, 0));
                    if (objectPtr == Q_NULLPTR) {
                        qWarning() << "Failed to construct subobject from QMetaObject,"
                                   << "did you forget to mark the constructor with Q_INVOKABLE?";
                    }
                    QObjectHelper::qvariant2qobject(iter.value().toMap(), objectPtr);
                    metaProperty.write(object, QVariant::fromValue(objectPtr));
                }
            }
        } else if (value.canConvert(type)) {
            value.convert(type);
            metaProperty.write(object, value);
        } else if (QLatin1String(metaProperty.typeName()) == QLatin1String("QVariant")) {
            metaProperty.write(object, value);
        }
    }
}

void QObjectHelper::qjsonobject2qobject(const QJsonObject &jsonObject, QObject *object)
{
    const QVariantMap map = jsonObject.toVariantMap();
    QObjectHelper::qvariant2qobject(map, object);
}
