#include "listelement.h"

#include <QDebug>

ListElement::ListElement() :
    mUserData("user_text"),
    mThreadCounter(0)
{
}

QString ListElement::className() const
{
    return this->metaObject()->className();
}

QString ListElement::userData() const
{
    return mUserData;
}

void ListElement::setUserData(const QString &userData)
{
    mUserData = userData;
}

int ListElement::threadCounter() const
{
    return mThreadCounter;
}

void ListElement::setThreadCounter(int threadCounter)
{
    mThreadCounter = threadCounter;
}
