#ifndef TESTQOBJECT_H
#define TESTQOBJECT_H

#include <QObject>
#include <QString>

#include "testqobject2.h"

class TestQObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(SubQObject* subObject READ subObject WRITE setSubObject NOTIFY subObjectChanged)

    Q_PROPERTY(int jsonDelimiter READ jsonDelimiter)

public:
    Q_INVOKABLE explicit TestQObject(QObject *parent = 0) { }

    int id() const { return m_id; }
    QString name() const { return m_name; }
    SubQObject* subObject() const { return m_subObject; }

    QObjectHelper::JsonDelimiter jsonDelimiter() const { return QObjectHelper::CamelCase; }

signals:
    void idChanged(int id);
    void nameChanged(QString name);
    void subObjectChanged(SubQObject *subObject);

public slots:
    void setId(int id)
    {
        if (m_id == id)
            return;

        m_id = id;
        emit idChanged(id);
    }

    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged(name);
    }

    void setSubObject(SubQObject *subObject)
    {
        if (m_subObject == subObject)
            return;

        m_subObject = subObject;
        emit subObjectChanged(subObject);
    }

private:
    int m_id;
    QString m_name;
    SubQObject *m_subObject;
};

Q_DECLARE_METATYPE(TestQObject*)

#endif // TESTQOBJECT_H
