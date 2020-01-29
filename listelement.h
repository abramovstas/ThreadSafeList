#ifndef LISTELEMENT_H
#define LISTELEMENT_H

#include <QObject>

const int classCount = 3;

class ListElement : public QObject
{
    Q_OBJECT
public:
    explicit ListElement();
    ~ListElement() {}

    QString userData() const;
    void setUserData(const QString &userData);

    int threadCounter() const;
    void setThreadCounter(int threadCounter);

    virtual QString className() const;

private:
    QString mUserData;
    int mThreadCounter;
};

class ListElement1 : public ListElement
{
    Q_OBJECT
public:
    explicit ListElement1() :
        ListElement() {}
    ~ListElement1() override {}
};

class ListElement2 : public ListElement
{
    Q_OBJECT
public:
    explicit ListElement2() :
        ListElement() {}
    ~ListElement2() override {}
};

#endif // LISTELEMENT_H
