#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <QString>
#include <queue>

class MessageQueue
{
public:
    static MessageQueue* getInstance();
    void push (QString str);
    QString pop ();
    bool empty();

private:
    MessageQueue();

    std::queue<QString> _queue;
};

#endif // MESSAGEQUEUE_H
