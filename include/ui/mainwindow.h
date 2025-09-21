#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <unordered_map>

#include "ui/errorwindow.h"
#include "ui/connect.h"
#include "lib/vpscraft.h"

struct VPSInstance {
    QPushButton* button;
    QLabel* img;
    QLabel* icon;
    QLabel* text;
};

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
    void onStarted(const char* instance);
    void updateInstances();

    Ui::MainWindow *ui;
    VPSCraft vps;
    QMessageBox error;
    QMessageBox info;
    ConnectWorker* connectWorker;
    QThread* thread;
    std::unordered_map<std::string, VPSInstance> _instances;
};
#endif // MAINWINDOW_H
