#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QState>
#include <QtCore/QPointer>
#include <QtCore/QModelIndex>
#include <QtWidgets/QAction>
#include <QtWidgets/QProgressDialog>







class MyObj : public QObject
{
    Q_OBJECT
public:

public Q_SLOTS:
    void slot1();
    void slot2() {};
    void slotWithArg(int i = 0) {};
Q_SIGNALS:
    void signal1();
};

void foo()
{
    MyObj *o1;
    MyObj *o2;

    o1->connect(o1, SIGNAL(signal1()), o2, SLOT(slot1()));
    o1->connect(o1, SIGNAL(signal1()), SLOT(slot1()));
    o1->connect(o1, SIGNAL(signal1()), SIGNAL(signal1()));
    QObject::connect(o1, SIGNAL(signal1()), o2, SIGNAL(signal1()));
    QObject::disconnect(o1, SIGNAL(signal1()), o2, SIGNAL(signal1()));

    o1->connect(o1, &MyObj::signal1, &MyObj::signal1);
    QObject::connect(o1, &MyObj::signal1, o2, &MyObj::signal1);
    QObject::disconnect(o1, &MyObj::signal1, o2, &MyObj::signal1);

    QTimer::singleShot(0, o1, SLOT(slot1()));
    QTimer::singleShot(0, o1, &MyObj::slot1);
    // QTimer doesn't support it with new connect syntax: Needs lambda
    QTimer::singleShot(0, o1, SLOT(slotWithArg()));
};


void MyObj::slot1()
{
    MyObj *o1;
    connect(o1, SIGNAL(signal1()), SLOT(slot2()));
}

class MyObjDerived : public MyObj
{
    Q_OBJECT
public:
    MyObjDerived()
    {
        connect(this, SIGNAL(signal1()), this, SLOT(slot2()));
        connect(this, SIGNAL(signal1()), SLOT(slot2()));
    }
};

void testDerived()
{
    MyObjDerived *o1;
    o1->connect(o1, SIGNAL(signal1()), o1, SLOT(slot2()));
    o1->connect(o1, SIGNAL(signal1()), SLOT(slot2()));
    QObject::connect(o1, SIGNAL(signal1()), o1, SLOT(slot2()));
}

class OtherObj : public QObject
{
    Q_OBJECT
public:
public Q_SLOTS:
    void otherSlot() {}
};

void testOther()
{
    OtherObj *other;
    MyObj *o1;
    other->connect(o1, SIGNAL(signal1()), SLOT(otherSlot()));
}

class WithNesting : public QObject
{
    Q_OBJECT
public Q_SLOTS:
    void slot1() {}
signals: void signal1();
private Q_SLOTS: void privSlot() {}
public:
    class Private;
    friend class Private;
};

class WithNesting::Private : public QObject
{
    Q_OBJECT
public:
    Private(WithNesting *q)
    {
        q->connect(q, SIGNAL(signal1()), SLOT(slot1()));
        connect(q, SIGNAL(signal1()), SLOT(pSlot1()));
        connect(q, SIGNAL(signal1()), q, SLOT(privSlot()));
        QTimer::singleShot(0, this, SLOT(privateSlot1())); // Testing if private slot gets fixed, it should due to "this"
    }
public Q_SLOTS:
    void pSlot1() {}
private Q_SLOT:
    void privateSlot1() {}
signals:
    void signal1();
};

void testNested()
{
     WithNesting::Private *p;
     QObject::connect(p, SIGNAL(signal1()), p, SLOT(privateSlot1())); // Warning, but can't fix, can't take address of private

     // QObject::connect(p, &WithNesting::Private::signal1, p, &WithNesting::Private::privateSlot1);
}

void testCharVariables(const char *methodName)
{
    QObject *o;
    QTimer::singleShot(0, o, methodName); // OK
    QObject::connect(o, methodName, 0, methodName); // OK
    o->connect(o, methodName, 0, methodName); // OK
    o->connect(o, SIGNAL(destroyed()), 0, methodName); // OK
}

void testQState()
{
    QState *s;
    QObject *o;
    s->addTransition(o, SIGNAL(destroyed()), s); // Warning
    s->addTransition(o, &QObject::destroyed, s); // OK

    WithNesting *wn;
    s->addTransition(wn, SLOT(privSlot()), s); // Warning, but can't fix
}

class TestingArgumentCounts : public QObject
{
    Q_OBJECT
public:
    TestingArgumentCounts()
    {
        connect(this, SIGNAL(si0()), SLOT(sl0())); // Warning and fixit
        connect(this, SIGNAL(si0()), SLOT(sl1(QString))); // Warning and can't fix
        connect(this, SIGNAL(si1(QString)), SLOT(sl0())); // Warning and can fix
        connect(this, SIGNAL(si2(QString)), SLOT(sl2())); // Warning and can't fix
    }
public Q_SLOTS:
    void sl0() {}
    void sl1(QString) {}
    void sl2(QString,QString,QString = QString()) {}

signals:
    void si0();
    void si1(QString);
    void si2(QString,QString);
    void si3(QString,QString,QString);
};


class TestingProtected : public QObject
{
    Q_OBJECT
protected Q_SLOT:
    void protec();
};


class DerivedTestingProtected : public TestingProtected
{
    void test()
    {
        connect(this, SIGNAL(destroyed()), this, SLOT(protec()));
    }
};


void testQPointer()
{
    QPointer<WithNesting> p8733 = new WithNesting();
    QObject::connect(p8733, SIGNAL(destroyed()), p8733, SLOT(deleteLater())); // Warning, and when fixed should have .data() due to gcc bug
    QObject::connect(p8733, &WithNesting::destroyed, p8733, &WithNesting::deleteLater);
    QObject::connect(p8733.data(), SIGNAL(destroyed()), p8733.data(), SLOT(deleteLater())); // Warning
    QObject::connect(p8733.data(), &WithNesting::destroyed, p8733.data(), &WithNesting::deleteLater);
    p8733->connect(p8733, SIGNAL(destroyed()), SLOT(deleteLater())); // Warning, but no-fix, not implemented. Fails to get implicit caller for now
}






struct S1
{
};

struct S2
{

};

struct S3
{
    S3(S2);
};

struct S1a : public S1
{

};

class TestTypes : public QObject
{
    Q_OBJECT
    TestTypes()
    {
        connect(this, SIGNAL(s1(bool)), SIGNAL(s2(int)));                           // Warning && fixit
        connect(this, SIGNAL(s2(int)), SIGNAL(s1(bool)));                           // Warning && fixit
        connect(this, SIGNAL(s2(int)), SIGNAL(s9(float)));                          // Warning && no-fixit
        connect(this, SIGNAL(s2(int)), SIGNAL(s10(double)));                        // Warning && no-fixit
        connect(this, SIGNAL(s9(float)), SIGNAL(s2(int)));                          // Warning && no-fixit
        connect(this, SIGNAL(s10(double)), SIGNAL(s2(int)));                        // Warning && no-fixit
        connect(this, SIGNAL(s10(double)), SIGNAL(s7(char)));                       // Warning && no-fixit
        connect(this, SIGNAL(s7(char)), SIGNAL(s10(double)));                       // Warning && no-fixit
        connect(this, SIGNAL(s3(int*)), SIGNAL(s1(bool)));                          // Warning && no-fixit
        connect(this, SIGNAL(s3(int*)), SIGNAL(s6(float *)));                       // Warning && no-fixit
        connect(this, SIGNAL(s1(bool)), SIGNAL(s3(int*)));                          // Warning && no-fixit
        connect(this, SIGNAL(doubleClicked(QModelIndex)), SIGNAL(triggered(bool))); // Warning && no-fixit
        connect(this, SIGNAL(s27(const S1 *)), SIGNAL(s23(const S1)));              // Warning && no-fixit
        connect(this, SIGNAL(s22(const S1)), SIGNAL(s27(const S1 *)));              // Warning && no-fixit
        connect(this, SIGNAL(s31(const S1 &)), SIGNAL(s31(const S1 &)));            // Warning && fixit
        connect(this, SIGNAL(s31(const S1 &)), SIGNAL(s23(const S1)));              // Warning && no-fixit // although we could make it work
    }

signals:
    void s1(bool);
    void s2(int);
    void s3(int *);
    void s4(bool *);
    void s5(float *);
    void s6(float *);
    void s7(char);
    void s8(char *);
    void s9(float);
    void s10(double);
    void s11(S1);
    void s12(S2);
    void s13(S3);
    void s14(S1a);
    void s15(S1*);
    void s16(S2*);
    void s17(S3*);
    void s18(S1a*);
    void s19(S1&);
    void s20(S2&);
    void s21(S3&);
    void s22(S1a&);

    void s23(const S1);
    void s24(const S2);
    void s25(const S3);
    void s26(const S1a);

    void s27(const S1 *);
    void s28(const S2 *);
    void s29(const S3 *);
    void s30(const S1a *);

    void s31(const S1 &);
    void s32(S1 &);

    void doubleClicked(const QModelIndex &);
    void triggered(bool yes = false);

};

namespace Kleo {
class ProgressDialog : public QProgressDialog
{
    Q_OBJECT
public:
    ProgressDialog(int ms);
};
}

Kleo::ProgressDialog::ProgressDialog(int ms)
{
    QTimer::singleShot(ms, this, SLOT(forceShow()));
}

struct P {
    QPointer<MyObj> ptr;
};


class TestQPointerMember : public QObject
{
    Q_OBJECT
public:
    TestQPointerMember()
    {
        QPointer<MyObj> ptr;
        connect(m_ptr, SIGNAL(signal1()), SLOT(slot1()));
        connect(m_ptr, SIGNAL(signal1()), m_ptr, SLOT(slot1()));
        connect(ptr, SIGNAL(signal1()), SLOT(slot1()));
        connect(ptr, SIGNAL(signal1()), ptr, SLOT(slot1()));
        connect(p->ptr, SIGNAL(signal1()), p->ptr.data(), SLOT(slot1()));
        connect(d_func()->ptr, SIGNAL(signal1()), d_func()->ptr.data(), SLOT(slot1()));
    }

    P* d_func() { return p; };

public Q_SLOTS:
    void slot1() {}

private:
    QPointer<MyObj> m_ptr;
    P *p;
};

int main() { return 0; }

#include "main.moc"