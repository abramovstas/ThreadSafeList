#ifndef MYWORKER_H
#define MYWORKER_H

#include <QObject>
#include <QTimer>

class ThreadSafeList;

class MyWorker : public QObject
{
    Q_OBJECT
public:
    explicit MyWorker(int interval = 1000, ThreadSafeList * list = nullptr, QObject *parent = nullptr);

public slots:
    void slotDoWork();
    void setInterval(int interval);

private slots:
    void setNextAction();

private:
    void addRandomElement();
    ThreadSafeList * m_list;
    int m_interval;
    QTimer* m_ptimer;
};

#endif // MYWORKER_H
