#ifndef LEDLABEL_H
#define LEDLABEL_H

#include <QWidget>

namespace Ui { class LedLabel; }

class LedLabel : public QWidget
{
public:
    enum led_color {red = 0, green = 1, yellow = 3, grey = 4};
    LedLabel(QWidget *parent = nullptr, QString text = "");
    void updateUI(int led_color, QString show_text = "");
    void clearText();
private:
    Ui::LedLabel *ui;

    // int current_leb_color;
    // QString current_text;

    const QString m_red_SheetStyle = "min-width: 12px; min-height: 12px;max-width:12px; max-height: 12px;border-radius: 6px;  border:1px solid black;background:red";
    const QString m_green_SheetStyle = "min-width: 12px; min-height: 12px;max-width:12px; max-height: 12px;border-radius: 6px;  border:1px solid black;background:green";
    const QString m_yellow_SheetStyle = "min-width: 12px; min-height: 12px;max-width:12px; max-height: 12px;border-radius: 6px;  border:1px solid black;background:yellow";
    const QString m_grey_SheetStyle = "min-width: 12px; min-height: 12px;max-width:12px; max-height: 12px;border-radius: 6px;  border:1px solid black;background:grey";
};

#endif // LEDLABEL_H
