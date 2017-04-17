#ifndef TESTQOBJECT3_H
#define TESTQOBJECT3_H

#include <QObject>
#include <QString>

class SubSubQObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString str READ str WRITE setStr)

public:
    Q_INVOKABLE explicit SubSubQObject(QObject *parent = 0) { }

    QString str() const { return m_string; }

public slots:
    void setStr(const QString &str)
    {
        if (m_string == str)
            return;

        m_string = str;
    }

private:
    QString m_string;
};

Q_DECLARE_METATYPE(SubSubQObject*)

#endif // TESTQOBJECT3_H
