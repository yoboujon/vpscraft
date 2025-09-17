#include "ui/mainwindow.h"
#include "./ui_mainwindow.h"

#include "lib/socket.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText(print_lib());
}

MainWindow::~MainWindow()
{
    delete ui;
}
