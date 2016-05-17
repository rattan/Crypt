#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>
#include <string>
using namespace std;
namespace Ui {
class Console;
}

class Console : public QWidget
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = 0);
    ~Console();


private:
    Ui::Console *ui;

private slots:
    void set_str(string str);
};

#endif // CONSOLE_H
