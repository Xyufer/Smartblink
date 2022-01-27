#include "gpio.h"
#include <lgpio.h>

Gpio::Gpio(QObject *parent) : QObject(parent)
{
    // initialization gpio
    m_handle = lgGpiochipOpen(CHIP);
    int init_state = 0;
    for (int pin : LEDS)
        lgGpioClaimOutput(m_handle, LFLAGS, pin, init_state);
}

Gpio::~Gpio()
{
    // LED's Ausschalten
    int state = 0;
    for (int pin : LEDS)
        lgGpioWrite(m_handle, pin, state);

    lgGpiochipClose(m_handle);
}

void Gpio::set(int pin, int state)
{
    lgGpioWrite(m_handle, pin, state);
}

void Gpio::set(unsigned int pattern)
{
    int n = 0;
    bool value;
    unsigned int check = 0b0001;
    for(auto pin : LEDS) {
        // n stelle von pattern ausmaskieren
        value = check & pattern >> n;
        lgGpioWrite(m_handle, pin, value);
        n++;
    }
}
