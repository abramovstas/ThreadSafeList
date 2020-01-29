#include "myworker.h"

#include <QRandomGenerator>
#include <QDebug>

#include "threadsafelist.h"
#include "listelement.h"

MyWorker::MyWorker(int interval, ThreadSafeList * list, QObject *parent) :
    QObject(parent),
    m_list(list),
    m_interval(interval),
    m_ptimer(new QTimer(this))
{
    connect(m_ptimer, &QTimer::timeout, this, &MyWorker::setNextAction);
}

void MyWorker::slotDoWork()
{
    m_ptimer->start(m_interval);
}

void MyWorker::setInterval(int interval)
{
    m_ptimer->stop();
    m_interval = interval;
    m_ptimer->start(m_interval);
}

void MyWorker::setNextAction()
{
    if (!m_list)
        return ;

    switch (QRandomGenerator::global()->bounded(quint32(0), quint32(classCount))) {
    case 0:
        addRandomElement();
        break;
    case 1:
        {
            auto element = m_list->pull(
                        int(QRandomGenerator::global()->bounded(quint32(0),
                                                                quint32(m_list->size())
                                                                )));
            if (element) {
                int counter = element->threadCounter();
                element->setThreadCounter(counter+=1);
                m_list->push(element);
            }
        }
        break;
    case 2:
        m_list->removeAt(
                    int(QRandomGenerator::global()->bounded(quint32(0),
                                                            quint32(m_list->size())
                                                            )));
        break;
    }
}

void MyWorker::addRandomElement()
{
    switch (QRandomGenerator::global()->bounded(quint32(0), quint32(classCount))) {
    case 0:
        m_list->append(new ListElement());
        break;
    case 1:
        m_list->append(new ListElement1());
        break;
    case 2:
        m_list->append(new ListElement2());
        break;
    }
}
