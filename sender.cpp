#include "sender.h"

Sender::Sender(QObject *parent) : QObject(parent)
{

}

void Sender::send_str(string str)
{
    _send_str(str);
}
