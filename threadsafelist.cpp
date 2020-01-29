#include "threadsafelist.h"
#include "listelement.h"

#include <QDebug>

ThreadSafeList::ThreadSafeList(QObject *parent) :
    QObject(parent)
{
}

ThreadSafeList::~ThreadSafeList()
{
    qDeleteAll(m_list);
}

void ThreadSafeList::append(ListElement* element)
{
    if (m_mutex.tryLock(2000)) {
        m_list.append(element);
        m_mutex.unlock();
        emit dataChanged();
    }
}

ListElement* ThreadSafeList::pull(int i)
{
    QMutexLocker loker(&m_mutex);
    if (m_list.size() > i) {
        foreach (ListElement *p_element, m_busyList) {
            if (p_element == m_list.at(i))
                return nullptr;
        }
        m_busyList.append(m_list.at(i));
        return m_list.at(i);
    }
    return nullptr;
}

void ThreadSafeList::lockElement(ListElement *element)
{
    foreach (ListElement *p_element, m_busyList) {
        if (p_element == element)
            return ;
    }
    m_busyList.append(element);
}

void ThreadSafeList::push(ListElement *element)
{
    QMutexLocker loker(&m_mutex);
    m_busyList.removeOne(element);
}

void ThreadSafeList::removeAt(int i)
{
    QMutexLocker loker(&m_mutex);
    if (m_list.size() > i) {
        foreach (ListElement *p_element, m_busyList) {
            if (p_element == m_list.at(i))
                return ;
        }
        m_list.removeAt(i);
        emit dataChanged();
    }
}

void ThreadSafeList::removeOne(ListElement *element)
{
    QMutexLocker loker(&m_mutex);
    m_list.removeOne(element);
}

int ThreadSafeList::size()
{
    QMutexLocker loker(&m_mutex);
    return m_list.size();
}

QList<ListElement *> ThreadSafeList::list_pull()
{
    m_mutex.lock();
    return m_list;
}

void ThreadSafeList::list_push()
{
    m_mutex.unlock();
}
