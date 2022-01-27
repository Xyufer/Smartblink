#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include "ui_gui.h"
#include "gpio.h"
#include <QTimer>

const int TIMEOUT = 1000;

class Gui : public QWidget, private Ui::Gui
{
    Q_OBJECT

public:
    explicit Gui(QWidget *parent = nullptr);

private slots:
    void on_speedSlider_valueChanged(int value);
    void on_blinkButton_clicked();
    void on_lauflichtButton_clicked();
    void toggle();

private:
    QTimer* m_timer;
    bool m_status;
    Gpio* m_leds;
    bool m_blink_lauf = 1;
    int cnt = 1;
};

#endif // GUI_H
