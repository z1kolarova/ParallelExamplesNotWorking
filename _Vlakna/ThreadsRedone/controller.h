#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>

class Controller : public QObject {
    Q_OBJECT
    QThread workerThread;
public:
    explicit Controller();
    ~Controller();

signals:
    void operate(int timeout);

public slots:
    void handleResults(int result);
};

#endif // CONTROLLER_H
