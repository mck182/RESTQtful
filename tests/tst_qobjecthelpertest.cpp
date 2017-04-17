#include <QString>
#include <QMetaType>
#include <QtTest>

#include "testqobject.h"
#include "testqobject2.h"
#include "../src/qobjecthelper.h"

class QObjectHelperTest : public QObject
{
    Q_OBJECT

public:
    QObjectHelperTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

QObjectHelperTest::QObjectHelperTest()
{
}

void QObjectHelperTest::initTestCase()
{
    qRegisterMetaType<TestQObject*>("TestQObject*");
    qRegisterMetaType<SubQObject*>("SubQObject*");
    qRegisterMetaType<SubSubQObject*>("SubSubQObject*");
}

void QObjectHelperTest::cleanupTestCase()
{
}

void QObjectHelperTest::testCase1()
{
    const QString jsonString = "{\"id\":1,\"name\":\"Hello\",\"subObject\":{\"id\":9,\"sub_sub_object\":{\"str\":\"SubSubObject\"}}}";
    QJsonDocument json = QJsonDocument::fromJson(jsonString.toUtf8());

    TestQObject *testObject = new TestQObject();
    QObjectHelper::qjsonobject2qobject(json.object(), testObject);

    QCOMPARE(testObject->id(), 1);
    QCOMPARE(testObject->name(), QStringLiteral("Hello"));
    QVERIFY(testObject->subObject() != Q_NULLPTR);
    QCOMPARE(testObject->subObject()->id(), 9);
    QVERIFY(testObject->subObject()->subSubObject() != Q_NULLPTR);
    QCOMPARE(testObject->subObject()->subSubObject()->str(), QStringLiteral("SubSubObject"));

    const QJsonObject jsonObject = QObjectHelper::qobject2qjsonobject(testObject);
    QCOMPARE(QJsonDocument(jsonObject).toJson(QJsonDocument::Compact), jsonString.toUtf8());
}

QTEST_APPLESS_MAIN(QObjectHelperTest)

#include "tst_qobjecthelpertest.moc"
