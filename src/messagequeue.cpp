#include "messagequeue.h"


MessageQueue::MessageQueue()
{

}


MessageQueue* MessageQueue::getInstance()
{
    static MessageQueue* _instance = new MessageQueue();
    return _instance;
}

void MessageQueue::push(QString str)
{
    _queue.push(str);
}

QString MessageQueue::pop()
{
    QString s = _queue.front();
    _queue.pop();

    return s;
}
bool MessageQueue::empty() {return _queue.empty();}
