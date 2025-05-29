#include <QCoreApplication>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QFutureWatcher<int> watcher;
    QObject::connect(&watcher, &QFutureWatcher<int>::finished, [&](){
        printf("Received result: %d\n", watcher.result());
    });

    printf("Starting calculation...\n");
    QFuture<int> future = QtConcurrent::run([](){
        QThread::sleep(3);
        return 1;
    });
    watcher.setFuture(future);

    return a.exec();
}
