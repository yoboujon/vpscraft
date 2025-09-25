#include "ui/mainwindow.h"
#include "./ui_mainwindow.h"

#include <QApplication>
#include <QTimer>
#include <QGraphicsColorizeEffect>
#include <QString>
#include <unordered_map>

#include "lib/error.h"

static inline void _set_effect(QLabel *label, const QColor &c)
{
    auto effect = new QGraphicsColorizeEffect(label);
    effect->setColor(c);
    effect->setStrength(0.8);
    label->setGraphicsEffect(effect);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), connectWorker(new ConnectWorker), thread(new QThread)
{
    ui->setupUi(this);

    // Setup Errors
    error.setIcon(QMessageBox::Critical);
    error.setWindowTitle("Error Occurred");
    error.setWindowIcon(QIcon(QString::fromUtf8(":/res/icon.ico")));
    // Setup Message
    info.setIcon(QMessageBox::Information);
    info.setWindowIcon(QIcon(QString::fromUtf8(":/res/icon.ico")));

    // Thread handlers
    connectWorker->set(ui->labelSSH, ui->imgSSH);
    connectWorker->moveToThread(thread);
    QObject::connect(thread, &QThread::started, connectWorker, &ConnectWorker::run);
    QObject::connect(thread, &QThread::finished, connectWorker, &QObject::deleteLater);
    QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    // Event handlers
    MainWindow::connect(ui->connectSSH, &QPushButton::clicked, this, &MainWindow::onSSHClicked);

    // Testing purposes
    _instances["craft2exile"] = {
        ui->buttonCTE2,
        ui->imgCTE2,
        ui->imgStatusCTE2,
        ui->statusCTE2,
    };
    _instances["atm10"] = {
        ui->buttonATM,
        ui->imgATM,
        ui->imgStatusATM,
        ui->statusATM,
    };

    for (const auto &i : _instances)
    {
        MainWindow::connect(i.second.button, &QPushButton::clicked, this,
                            [this, i]()
                            {
                                this->onStarted(i.first.c_str());
                            });
        _set_effect(i.second.img, Qt::darkGray);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setError(const std::string &title, const std::string &description)
{
    error.setText(QString::fromStdString(title));
    error.setInformativeText(QString::fromStdString(description));
}

void MainWindow::updateInstances()
{
    const auto list = vps.get_active_list();
    const QPixmap on(":/res/radio_on.png"), off(":/res/radio_off.png");

    for (const auto &l : list)
    {
        auto it = _instances.find(l.first);
        if (it == _instances.end())
            continue;
        if (l.second)
        {
            it->second.img->setGraphicsEffect(nullptr);
            it->second.icon->setPixmap(on);
            it->second.text->setText(" Started");
            it->second.button->setDisabled(true);
        }
        else
        {
            _set_effect(it->second.img, Qt::darkGray);
            it->second.icon->setPixmap(off);
            it->second.text->setText(" Stopped");
            it->second.button->setDisabled(false);
        }
    }
}

void MainWindow::onSSHClicked()
{
    info.setWindowTitle("Connecting through ssh...");
    info.setText(QString::fromUtf8("Connecting to 'mc.etheryo.fr'..."));
    info.show();
    QCoreApplication::processEvents();
    try
    {
        vps.init("mc.etheryo.fr", "root");
    }
    catch (const VPSError &err)
    {
        info.close();
        if (!err.more().empty())
            setError(err.what(), err.more());
        else
            setError(err.what(), "");
        ui->labelSSH->setText(QString::fromUtf8(err.what()));
        error.exec();
        return;
    }

    // Successful
    ui->imgSSH->setPixmap(QPixmap(":/res/radio_on.png"));
    ui->labelSSH->setText("Connected");
    ui->connectSSH->setDisabled(true);
    updateInstances();
    info.close();
}

void MainWindow::onStarted(const char *instance)
{
    info.setWindowTitle("Starting Instance...");
    info.setText(QString::fromStdString(std::string("Starting '") + instance + "'..."));
    info.show();
    QCoreApplication::processEvents();
    // Disabling buttons, setting instance
    for (const auto &i : _instances)
    {
        i.second.button->setDisabled(true);
        vps.set_instance(i.first, false);
    }
    vps.set_instance(instance, true);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, timer, instance]()
            {
    if (vps.get_active(instance)) {
        info.close();
        updateInstances();
        timer->stop();
        timer->deleteLater();
    } });
    timer->start(300);
}
