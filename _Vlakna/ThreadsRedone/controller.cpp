#include "controller.h"
#include "worker.h"

Controller::Controller() {
    Worker *worker = new Worker;
    worker->moveToThread(&workerThread);

    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Controller::operate, worker, &Worker::doWork);
    connect(worker, &Worker::resultReady, this, &Controller::handleResults);

    workerThread.start();
}

Controller::~Controller() {
    workerThread.quit();
    workerThread.wait();
}

void Controller::handleResults(int result) {
    printf("Received result: %d\n", result);
}
