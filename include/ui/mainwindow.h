#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "ui/errorwindow.h"
#include "ui/connect.h"
#include "lib/vpscraft.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setError(const std::string &title, const std::string &description);
    void onSSHClicked();

    Ui::MainWindow *ui;
    VPSCraft vps;
    QMessageBox error;
    ConnectWorker* connectWorker;
    QThread* thread;
};
#endif // MAINWINDOW_H
