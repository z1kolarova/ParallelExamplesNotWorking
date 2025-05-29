#include <QThread>

#include "worker.h"

void Worker::doWork(int timeout)
{
    printf("Working...\n");
    QThread::sleep(timeout);
    printf("Done, sending result.\n");

    emit resultReady(rand() % 1000);
}
