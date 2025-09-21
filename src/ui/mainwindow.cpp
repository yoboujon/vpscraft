#include "ui/mainwindow.h"
#include "./ui_mainwindow.h"

#include <QApplication>

#include "lib/ssh.h"
#include "lib/error.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    error.setIcon(QMessageBox::Critical);
    error.setWindowTitle("Error Occurred");
    error.setWindowIcon(QIcon(QString::fromUtf8(":/res/icon.ico")));
    MainWindow::connect(ui->connectSSH, &QPushButton::clicked, this, &MainWindow::onSSHClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setError(const std::string &title, const std::string &description)
{
    error.setText(QString::fromUtf8(title));
    error.setInformativeText(QString::fromUtf8(description));
}

void MainWindow::onSSHClicked()
{
    try
    {
        connect_ssh();
    }
    catch (const VPSError &err)
    {
        if (!err.more().empty())
            setError(err.what(), err.more());
        else
            setError(err.what(), "");
        ui->labelSSH->setText(QString::fromUtf8(err.what()));
        error.exec();
    }
}
