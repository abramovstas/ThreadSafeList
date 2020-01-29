#ifndef THREADSAFELIST_H
#define THREADSAFELIST_H

#include <QObject>
#include <QMutex>

class ListElement;

class ThreadSafeList : public QObject
{
    Q_OBJECT
public:
    explicit ThreadSafeList(QObject *parent = nullptr);
    ~ThreadSafeList();

    void append(ListElement* element);
    ListElement* pull(int i);
    void lockElement(ListElement *element);
    void push(ListElement* element);
    void removeAt(int i);
    void removeOne(ListElement *element);
    int size();

    QList<ListElement *> list_pull();
    void list_push();

signals:
    void dataChanged();

public slots:

private:
    QMutex m_mutex;
    QList<ListElement*> m_list;
    QList<ListElement*> m_busyList;
};

#endif // THREADSAFELIST_H
