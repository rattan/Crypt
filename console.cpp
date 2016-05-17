#include "console.h"
#include "ui_console.h"

Console::Console(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);
        setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

Console::~Console()
{
    delete ui;
}

void Console::set_str(string str)
{
    this->ui->edit_console->append(QString::fromStdString(str));
}
