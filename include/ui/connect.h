#ifndef CONNECT_H
#define CONNECT_H

#include <QObject>
#include <QThread>
#include <QLabel>
#include <QPixmap>

class ConnectWorker : public QObject
{
    Q_OBJECT
public:
    explicit ConnectWorker(QObject *parent = nullptr)
        : QObject(parent), stopped(false)
    {
    }
public slots:
    void run()
    {
        while (!stopped)
        {
            imgSSH->setPixmap(QPixmap(":/res/radio_wait.png"));
            QThread::msleep(200);
            imgSSH->setPixmap(QPixmap(":/res/radio_unknown.png"));
        }
    }

    void set(QLabel *label, QLabel *icon)
    {
        labelSSH = label;
        imgSSH = icon;
    }

    void stop() { stopped = true; }

private:
    bool stopped;
    QLabel *labelSSH;
    QLabel *imgSSH;
};

#endif // CONNECT_H