#include "server_thread.h"
#include "messagequeue.h"
#include "settings.h"

#include <string>
#include <iostream>
#include <QCoreApplication>
#include <QStringList>
#include <QDebug>

ServerThread::ServerThread()
{
    connect(&_serv_process, SIGNAL(readyReadStandardOutput()), this, SLOT(on_ready_read()));
    connect(&_serv_process, SIGNAL(finished(int)), this, SLOT(on_server_stoped()));
}


void ServerThread::start()
{
    QString jar = QString ("");
    jar.append(Settings::getInstance()->get_working_dir());
    jar.append("/");
    jar.append(Settings::getInstance()->get_jar());

    QStringList args;
    args << QString("-Xmx").append(QString::number(Settings::getInstance()->get_ram())).append("M");
    args << QString("-Xms").append(QString::number(Settings::getInstance()->get_ram())).append("M");
    args << "-jar";
    args << jar;
    args << "nogui";


    _serv_process.setProgram("java");
    _serv_process.setArguments(args);
    _serv_process.setWorkingDirectory(Settings::getInstance()->get_working_dir());
    _serv_process.open(QProcess::ReadWrite);

     emit server_starting();
}

void ServerThread::force_stop()
{
    _serv_process.kill();
}
void ServerThread::soft_stop()
{
    send_command(QString ("/stop"));
}
void ServerThread::send_command (QString command)
{
    if(is_running())
    {
        _serv_process.write(command.toLocal8Bit());
        _serv_process.write("\n");
    }

}


bool ServerThread::is_running()
{
    return _serv_process.state()==QProcess::Running;
}

void ServerThread::on_ready_read()
{
    char buf1 [300] = {};
    _serv_process.readLine(buf1, sizeof(buf1));
    QString message (buf1);
    MessageQueue::getInstance()->push(message);

    char buf2[300] = {};
    int result = _serv_process.readLine(buf2, sizeof(buf2));
    if (result != 0 && result != -1)
    {
        QString message (buf2);
        MessageQueue::getInstance()->push(message);
    }
}

void ServerThread::on_server_stoped()
{
    emit server_stoped();
}




