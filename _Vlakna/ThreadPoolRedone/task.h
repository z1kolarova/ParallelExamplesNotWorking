#ifndef TASK_H
#define TASK_H

#include <QRunnable>
#include <QThread>

#define TASK_MAX_COUNT (5)

class Task : public QRunnable
{
public:
    Task(int delay);

protected:
    virtual void run();
    int m_delay = -1;
};

#endif // TASK_H
