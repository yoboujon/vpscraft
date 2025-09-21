#include "ui/errorwindow.h"
#include "./ui_errorwindow.h"

#include <QApplication>
#include <QLabel>
#include <QStyle>
#include <QPixmap>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->errorIcon->setPixmap(
        QApplication::style()->standardPixmap(QStyle::SP_MessageBoxCritical));
}

Dialog::~Dialog()
{
    delete ui;
}
