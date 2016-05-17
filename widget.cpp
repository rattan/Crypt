#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    ch_key(false),
    ch_key_h(false),
    ch_plain_h(false),
    ch_plain(false),
    ch_cipher_h(false),
    ch_cipher(false)
{
    ui->setupUi(this);

//    setAttribute(Qt::WA_TranslucentBackground); //enable MainWindow to be transparent
//    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    QGraphicsDropShadowEffect *effect[9];
    for(int i=0;i<9;++i)
    {
        effect[i] = new QGraphicsDropShadowEffect();
        effect[i]->setBlurRadius(15);
        effect[i]->setColor(Qt::white);
        effect[i]->setOffset(0,0);
    }
    this->ui->label->setGraphicsEffect(effect[0]);
    this->ui->label_2->setGraphicsEffect(effect[1]);
    this->ui->label_3->setGraphicsEffect(effect[2]);
    this->ui->label_4->setGraphicsEffect(effect[3]);

    this->ui->radio_des->setGraphicsEffect(effect[4]);
    this->ui->radio_aes->setGraphicsEffect(effect[5]);
    this->ui->radio_128->setGraphicsEffect(effect[6]);
    this->ui->radio_192->setGraphicsEffect(effect[7]);
    this->ui->radio_256->setGraphicsEffect(effect[8]);

    connect(&des.sender,SIGNAL(_send_str(string)),&console,SLOT(set_str(string)));
    connect(&aes.sender,SIGNAL(_send_str(string)),&console,SLOT(set_str(string)));
    console.show();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_push_enc_clicked()
{
    QString key = this->ui->line_key->text();
    QString PlainText = this->ui->text_plain->toPlainText();
    QString CipherText = "";
    if(this->ui->radio_des->isChecked())
    {
        des.setKey(key.toStdWString());
        for(int i=0;i<PlainText.length();i+=4)
        {
            CipherText += QString::fromStdWString(des.Encrypt(PlainText.mid(i,4).toStdWString()));
        }
    }
    else if(this->ui->radio_aes->isChecked())
    {
        if(this->ui->radio_128->isChecked()) aes.setKey(key.toStdWString(),Aes::keylen_128);
        else if(this->ui->radio_192->isChecked()) aes.setKey(key.toStdWString(),Aes::keylen_192);
        else if(this->ui->radio_256->isChecked()) aes.setKey(key.toStdWString(),Aes::keylen_256);
        for(int i=0;i<PlainText.length();i+=8)
        {
            CipherText += QString::fromStdWString(aes.Encrypt(PlainText.mid(i,8).toStdWString()));
        }
    }
    this->ui->text_cipher->setText(CipherText);
}

void Widget::on_push_dec_clicked()
{
    QString key = this->ui->line_key->text();
    QString PlainText = "";
    QString CipherText = this->ui->text_cipher->toPlainText();
    if(this->ui->radio_des->isChecked())
    {
        des.setKey(key.toStdWString());
        for(int i=0;i<CipherText.length();i+=4)
        {
            PlainText += QString::fromStdWString(des.Decrypt(CipherText.mid(i,4).toStdWString()));
        }
    }
    else if(this->ui->radio_aes->isChecked())
    {
        if(this->ui->radio_128->isChecked()) aes.setKey(key.toStdWString(),Aes::keylen_128);
        else if(this->ui->radio_192->isChecked()) aes.setKey(key.toStdWString(),Aes::keylen_192);
        else if(this->ui->radio_256->isChecked()) aes.setKey(key.toStdWString(),Aes::keylen_256);
        for(int i=0;i<CipherText.length();i+=8)
        {
            PlainText += QString::fromStdWString(aes.Decrypt(CipherText.mid(i,8).toStdWString()));
        }
    }
    this->ui->text_plain->setText(PlainText);
}

void Widget::on_text_plain_textChanged()
{
    if(ch_plain_h) return;
    ch_plain = true;
    QString hex = "";
    for(auto c:ui->text_plain->toPlainText())
    {
        QString temp;
        temp.sprintf("%04X ",c.unicode());
        hex+=temp;
    }
    hex.remove(hex.length()-1,1);
    ui->text_plain_hex->setText(hex);
    ch_plain = false;
}

void Widget::on_text_plain_hex_textChanged()
{
    if(ch_plain) return;
    ch_plain_h = true;
    QString res;
    for(auto s:this->ui->text_plain_hex->toPlainText().split(' '))
    {
        int si = s.toInt(0,16);
        QChar t(si);
        res+=t;
    }
    this->ui->text_plain->setText(res);
    ch_plain_h = false;
}

void Widget::on_text_cipher_textChanged()
{
    if(ch_cipher_h) return;
    ch_cipher = true;
    QString hex = "";
    for(auto c:ui->text_cipher->toPlainText())
    {
        QString temp = "";
        temp.sprintf("%04X ",c.unicode());
        hex+=temp;
    }
    hex.remove(hex.length()-1,1);
    ui->text_cipher_hex->setText(hex);
    ch_cipher = false;
}
void Widget::on_text_cipher_hex_textChanged()
{
    if(ch_cipher) return;
    ch_cipher_h = true;
    QString res;
    for(auto s:this->ui->text_cipher_hex->toPlainText().split(' '))
    {
        int si = s.toInt(0,16);
        QChar t(si);
        res+=t;
    }
    this->ui->text_cipher->setText(res);
    ch_cipher_h = false;
}

void Widget::on_line_key_textChanged(const QString &arg1)
{
    if(ch_key_h) return;
    ch_key = true;
    QString hex = "";
    for(auto c:arg1)
    {
        QString temp = "";
        temp.sprintf("%04X ",c.unicode());
        hex+=temp;
    }
    hex.remove(hex.length()-1,1);
    this->ui->line_key_hex->setText(hex);
    ch_key = false;
}
void Widget::on_line_key_hex_textChanged(const QString &arg1)
{
    if(ch_key) return;
    ch_key_h = true;
    QString res;
    for(auto s:arg1.split(' '))
    {
        int si = s.toInt(0,16);
        QChar t(si);
        res+=t;
    }
    this->ui->line_key->setText(res);
    ch_key_h = false;
}




void Widget::on_radio_des_clicked()
{
    this->ui->radio_128->setDisabled(true);
    this->ui->radio_192->setDisabled(true);
    this->ui->radio_256->setDisabled(true);
}

void Widget::on_radio_aes_clicked()
{
    this->ui->radio_128->setEnabled(true);
    this->ui->radio_192->setEnabled(true);
    this->ui->radio_256->setEnabled(true);
}

void Widget::on_push_console_clicked()
{
    if(console.isHidden()) console.show();
    else console.hide();
}

void Widget::closeEvent(QCloseEvent *e)
{
    console.close();
}

