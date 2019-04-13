#include "message_processing_thread.h"
#include "mainwindow.h"
#include "settings.h"
#include <messagequeue.h>
#include <iostream>
#include <QDebug>

MessageProcessingThread::MessageProcessingThread():
    processing_messages (true)
{

}


void MessageProcessingThread::run()
{
    processing_messages = true;
    while (processing_messages || !MessageQueue::getInstance()->empty())
    {
        if (!MessageQueue::getInstance()->empty()){
            QString message = MessageQueue::getInstance()->pop();
            message.resize(message.length()-2);

            process_message(message);
        }
    }
}

void MessageProcessingThread::process_message(QString message)
{
    switch (get_message_type(message)) {
        case MessageType::info:
            if (Settings::get_instance()->get_log_level() == Settings::LogLevel::info)
            {
                emit print_info(message);
            }
            break;
        case MessageType::warn:
            if (Settings::get_instance()->get_log_level() == Settings::LogLevel::warn ||
                Settings::get_instance()->get_log_level() == Settings::LogLevel::info)
            {
                emit print_warn(message);
            }
            break;
        case MessageType::error:
            emit print_error(message);
            break;
    }

    if (is_server_running (message)) emit server_running();

    QString player_name ("");

    player_name = is_player_joined_the_game(message);
    if (player_name.length() > 0) emit make_player_online(player_name);
    else
    {
        player_name = is_player_left_the_game(message);
        if (player_name.length() > 0) emit make_player_offline(player_name);
        else
        {
            player_name = is_player_opped(message);
            if (player_name.length() > 0) emit make_player_opped(player_name);
            else
            {
                player_name = is_player_deopped(message);
                if (player_name.length() > 0) emit make_player_deopped(player_name);
                else
                {
                    player_name = is_player_banned(message);
                    if (player_name.length() > 0) emit make_player_banned(player_name);
                    else
                    {
                        player_name = is_player_unbanned(message);
                        if (player_name.length() > 0) emit make_player_unbanned(player_name);
                    }
                }
            }
        }
    }
}

void MessageProcessingThread::stop()
{
    processing_messages = false;
}





MessageProcessingThread::MessageType MessageProcessingThread::get_message_type(QString message)
{
    int start_pos =  message.indexOf('/')+1;
    int end_pos = message.indexOf(']', start_pos);
    QString mes_type_str = message.mid(start_pos, (end_pos-start_pos));

    if (!mes_type_str.compare(QString("INFO"))) return MessageType::info;
    if (!mes_type_str.compare(QString("WARN"))) return MessageType::warn;
    if (!mes_type_str.compare(QString("ERROR"))) return MessageType::error;

    return MessageType::info;
}

bool MessageProcessingThread::is_server_running(QString message)
{
    return message.indexOf(QString("Done")) != -1;
}

QString MessageProcessingThread::is_player_joined_the_game(QString message)
{
    QString player_name ("");
    int end_pos = message.indexOf(QString ("joined the game"));
    if (end_pos != -1){
        int start_pos = message.lastIndexOf(":", end_pos)+2;
        player_name = message.mid(start_pos, end_pos-start_pos-1);
    }

    return player_name;
}
QString MessageProcessingThread::is_player_left_the_game(QString message)
{
    QString player_name ("");
    int end_pos = message.indexOf(QString ("left the game"));
    if (end_pos != -1){
        int start_pos = message.lastIndexOf(":", end_pos)+2;
        player_name = message.mid(start_pos, end_pos-start_pos-1);
    }

    return player_name;
}

QString MessageProcessingThread::is_player_opped(QString message)
{
    QString player_name ("");
    int start_pos = message.indexOf(QString ("Opped"));
    if (start_pos != -1){
        player_name = message.mid(start_pos+6, message.length()-(start_pos+6));
    }

    return player_name;
}

QString MessageProcessingThread::is_player_deopped(QString message)
{
    QString player_name ("");
    int start_pos = message.indexOf(QString ("De-opped"));
    if (start_pos != -1){
        player_name = message.mid(start_pos+9, message.length()-(start_pos+9));
    }

    return player_name;
}

QString MessageProcessingThread::is_player_banned(QString message)
{
    QString player_name ("");
    int start_pos = message.indexOf(QString ("Banned player"));
    if (start_pos != -1){
        player_name = message.mid(start_pos+14, message.length()-(start_pos+14));
    }

    return player_name;
}

QString MessageProcessingThread::is_player_unbanned(QString message)
{
    QString player_name ("");
    int start_pos = message.indexOf(QString ("Unbanned player"));
    if (start_pos != -1){
        player_name = message.mid(start_pos+16, message.length()-(start_pos+16));
    }

    return player_name;
}









































