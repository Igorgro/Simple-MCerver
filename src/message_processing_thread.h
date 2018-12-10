#ifndef MESSAGE_PROCESSING_THREAD_H
#define MESSAGE_PROCESSING_THREAD_H

#include <QObject>
#include <QString>
#include <QThread>


class MessageProcessingThread : public QThread
{
    Q_OBJECT
    enum MessageType {info, warn, error};

public:
    MessageProcessingThread ();
    void run();
    void stop();



signals:
    void server_running();
    void print_info (QString message);
    void print_warn (QString message);
    void print_error (QString message);
    void make_player_online (QString player_name);
    void make_player_offline (QString player_name);
    void make_player_opped (QString player_name);
    void make_player_deopped (QString player_name);
    void make_player_banned (QString player_name);
    void make_player_unbanned (QString player_name);

private:
    volatile bool processing_messages;

    void process_message(QString message);

    bool is_server_running (QString message);
    MessageType get_message_type (QString message);
    QString is_player_joined_the_game (QString message);
    QString is_player_left_the_game (QString message);
    QString is_player_opped (QString message);
    QString is_player_deopped (QString message);
    QString is_player_banned (QString message);
    QString is_player_unbanned (QString message);
};

#endif // MESSAGE_PROCESSING_THREAD_H
