#ifndef WIDGET_H
#define WIDGET_H

/*
 * Widget.h
 * Written by Rattan
 * Version control : https://github.com/rattan/Ctypt
 * copyright (c) 2016 Kang Jin Gu. All rights reserved
 * Follow General Public License(GPL)
 * Create File : 2016/04/15
 * Last Modify : 2016/05/14
 * This Widget shows crypt interface.
 * It include 4 text edits, 2 line edits, 5 radio buttons, 2 buttons and some static texts.
 * Editor with 'Hex', it shows 4 digits hexa-decimal.
 * Others are accept plain text.
 * Plain and hex editor are linked in real time covert.
 */

#include <QWidget>
#include <QGraphicsDropShadowEffect>

#include "des.h"
#include "aes.h"
#include "console.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    Console console;

private slots:
    void on_push_enc_clicked();

    void on_push_dec_clicked();

    void on_text_plain_textChanged();
    void on_text_plain_hex_textChanged();

    void on_text_cipher_hex_textChanged();
    void on_text_cipher_textChanged();

    void on_line_key_textChanged(const QString &arg1);
    void on_line_key_hex_textChanged(const QString &arg1);

    void on_radio_des_clicked();

    void on_radio_aes_clicked();

    void on_push_console_clicked();

private:
    Ui::Widget *ui;
    Des des;
    Aes aes;

    bool ch_key_h,ch_key;
    bool ch_plain_h,ch_plain;
    bool ch_cipher_h,ch_cipher;

    void closeEvent(QCloseEvent* e);

    template<size_t _S>
    QString arrtoqstr(array<uint8_t,_S> arr);

    void _set_aes_key(QString key);


};

#endif // WIDGET_H
