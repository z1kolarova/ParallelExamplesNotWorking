#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonOpenClose_clicked();

    void on_lineEdit_returnPressed();

    void statusChanged(QProcess::ProcessState state);
    void readyToRead();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processErrorOccured(QProcess::ProcessError error);

private:
    Ui::MainWindow *ui;
    QProcess echo;

    void updateUI(bool enable);
};

#endif // MAINWINDOW_H
