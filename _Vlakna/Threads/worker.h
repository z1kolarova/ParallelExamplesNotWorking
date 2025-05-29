#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject {
    Q_OBJECT
public:
signals:
    void resultReady(int result);

public slots:
    void doWork(int timeout);
};

#endif // WORKER_H
