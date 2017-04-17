#ifndef TESTQOBJECT2_H
#define TESTQOBJECT2_H

#include <QObject>

#include <qobjecthelper.h>

#include "testqobject3.h"

class SubQObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(SubSubQObject* subSubObject READ subSubObject WRITE setSubSubQObject NOTIFY subSubQObjectChanged)

    Q_PROPERTY(int jsonDelimiter READ jsonDelimiter)

public:
    Q_INVOKABLE explicit SubQObject(QObject *parent = 0) { }

    int id() const { return m_id; }
    SubSubQObject* subSubObject() const { return m_subSubQObject; }

    QObjectHelper::JsonDelimiter jsonDelimiter() const { return QObjectHelper::Underscore; }

signals:
    void idChanged(int id);
    void subSubQObjectChanged(SubSubQObject *subSubObject);

public slots:
    void setId(int id)
    {
        if (m_id == id)
            return;

        m_id = id;
        emit idChanged(id);
    }

    void setSubSubQObject(SubSubQObject *subSubQObject)
    {
        if (m_subSubQObject == subSubQObject)
            return;

        m_subSubQObject = subSubQObject;
        emit subSubQObjectChanged(subSubQObject);
    }

private:
    int m_id;
    SubSubQObject *m_subSubQObject;
};

Q_DECLARE_METATYPE(SubQObject*)

#endif // TESTQOBJECT2_H
