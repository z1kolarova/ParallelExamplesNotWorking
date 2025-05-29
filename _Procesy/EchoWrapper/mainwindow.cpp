#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileInfo>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateUI(false);

    connect(&echo, &QProcess::readyReadStandardOutput, this, &MainWindow::readyToRead);
    connect(&echo, &QProcess::stateChanged, this, &MainWindow::statusChanged);
    connect(&echo, &QProcess::errorOccurred, this, &MainWindow::processErrorOccured);
    connect(&echo, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &MainWindow::processFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonOpenClose_clicked()
{
    switch (echo.state()) {
    case QProcess::NotRunning:
        // Echo application must reside in the same folder as EchoWrapper
        echo.setWorkingDirectory(QCoreApplication::applicationDirPath());
        echo.start("./Echo");
        break;

    case QProcess::Running:
    case QProcess::Starting:
        echo.terminate();
        break;

    default:
        break;
    }
}

void MainWindow::on_lineEdit_returnPressed()
{
    echo.write(QString(ui->lineEdit->text() + "\n").toLocal8Bit());
}

void MainWindow::statusChanged(QProcess::ProcessState state)
{
    switch (state) {
    case QProcess::NotRunning:
        ui->buttonOpenClose->setText(tr("Start Echo process"));
        updateUI(false);
        break;

    case QProcess::Running:
    case QProcess::Starting:
        ui->buttonOpenClose->setText(tr("Close Echo process"));
        updateUI(true);
        break;

    default:
        break;
    }
}

void MainWindow::readyToRead()
{
    ui->plainTextEdit->appendPlainText(echo.readAllStandardOutput());
}

void MainWindow::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if(ui->action_Track_errors->isChecked()) {
        switch (exitStatus) {
        case QProcess::Crashed:
            QMessageBox::critical(this, tr("Echo Wrapper"), tr("Echo process has crashed."));
            break;

        case QProcess::NormalExit:
            QMessageBox::warning(this, tr("Echo Wrapper"), QString("Echo process has exited with return value %1.").arg(exitCode));
            break;

        default:
            break;
        }
    }
}

void MainWindow::processErrorOccured(QProcess::ProcessError error)
{
    if(ui->action_Track_errors->isChecked()) {
        QMessageBox::critical(this, tr("Echo Wrapper"), tr("Error %1 has occured.").arg(error));
    }
}

void MainWindow::updateUI(bool enable)
{
    ui->lineEdit->setEnabled(enable);
    ui->plainTextEdit->setEnabled(enable);
}
