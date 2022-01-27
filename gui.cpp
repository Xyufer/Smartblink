#include "gui.h"

Gui::Gui(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    m_leds = new Gpio(this);
    m_timer = new QTimer(this);

    m_status = false;
    //Verbinde: Quelle(Timer aus klasse Timer) -> Zeil (Toggel-Funktion aus Klasse Gui)
    connect(m_timer, &QTimer::timeout, this, &Gui::toggle);
    m_timer->start(1000); // Frequenz auf 1 s, weil m_timer sich unten erst mit der value ändert, wenn Slider verschoben wird
    // Deswegen Standardmaessig 1 s
}

void Gui::on_speedSlider_valueChanged(int value)
{
    m_timer->start(1000/value); // Frequenz mit Slider geändert
}

void Gui::on_blinkButton_clicked()
{
    m_blink_lauf = 1; // Blinklicht bei 1
    cnt = 0; // counter startet bei 0 -> keine led an
}

void Gui::on_lauflichtButton_clicked()
{
    m_blink_lauf = 0; // Lauflicht bei 0
    cnt = 1; // counter startet bei 1 -> 1ste led an
}

void Gui::toggle()
{
    // Blinklicht
    if(m_blink_lauf) {
        m_status = !m_status; // schaltet immer um -> blinken
        if(m_status == 1)
            cnt = 15; // alle leds
        else
            cnt = 0; // keine led
    }

    // Lauflicht
    if(!m_blink_lauf) {
        if(cnt < 8)
            cnt = cnt * 2; // jede led nacheinander
        else
            cnt = 1; // wieder 1ste led
    }

    m_leds->set(cnt); // leds setzen
}
