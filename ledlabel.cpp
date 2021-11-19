#include "ledlabel.h"
#include "ui_ledlabel.h"

LedLabel::LedLabel(QWidget *parent, QString text)
    :QWidget(parent)
    ,ui(new Ui::LedLabel)
{
    ui->setupUi(this);
    ui->horizontalLayout->setContentsMargins(1, 0, 7, 0);
    ui->led_label->clear();

    this->updateUI(red, text);
}

void LedLabel::updateUI(int led_color, QString show_text)
{
    switch (led_color)
    {
    case red:
    {
        ui->led_label->setStyleSheet(this->m_red_SheetStyle);
        break;
    }
    case green:
    {
        ui->led_label->setStyleSheet(this->m_green_SheetStyle);
        break;
    }
    case yellow:
    {
        ui->led_label->setStyleSheet(this->m_yellow_SheetStyle);
        break;
    }
    case grey:
    {
        ui->led_label->setStyleSheet(this->m_grey_SheetStyle);
        break;
    }
    default:
        break;
    }

    if (show_text != "")
    {
        ui->text_label->setText(show_text);
    }
}

void LedLabel::clearText()
{
    ui->text_label->clear();
}
