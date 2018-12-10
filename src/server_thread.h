#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <QProcess>
#include <QThread>
#include <QObject>

class ServerThread : public QObject
{
    Q_OBJECT
private:
    QProcess _serv_process;

public:
    ServerThread();
    void start();
    void force_stop();
    void soft_stop();
    void send_command (QString command);

    bool is_running();
signals:
    void server_stoped();
    void server_starting();

public slots:
    void on_ready_read();
    void on_server_stoped();


};

#endif // SERVER_THREAD_H
