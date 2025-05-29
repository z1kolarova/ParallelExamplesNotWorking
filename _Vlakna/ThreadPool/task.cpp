#include "task.h"

Task::Task(int delay)
{
    m_delay = delay;
}

void Task::run()
{
    printf("Message from thread with delay %ds - STARTING...\n", m_delay);
    QThread::sleep(m_delay);
    printf("Message from thread with delay %ds - FINISHED.\n", m_delay);
}
