#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <string>
using namespace std;
class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = 0);

    void send_str(string str);
signals:
    void _send_str(string str);

public slots:
};

#endif // SENDER_H
