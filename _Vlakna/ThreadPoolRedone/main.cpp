#include <QCoreApplication>
#include <QThreadPool>

#include "task.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThreadPool::globalInstance()->setMaxThreadCount(TASK_MAX_COUNT);

    for(int i=1; i<=TASK_MAX_COUNT; ++i)
        QThreadPool::globalInstance()->start(new Task(i));

    return a.exec();
}
