/*

    Voltage: 3.3V, 5V
    Output load voltage :0-24V
    Output load current: <5A (1A above need to add heat sink)
    Using original IRF520 Power MOS, you can adjust the output PWM
    Arduino drive up to 24V allows the load, such as LED lights, DC motors, miniature pumps, solenoid valves
    PWM dimming LED can be used to achieve stepless dimming, variable speed motor
    Size: 33*24mm
    Weight: 10g
    Ports: Digital Level
    Platform: Arduino, MCU, ARM, raspberry pie

*/
#include "Arduino.h"

class MOSFET_IRF520
{
private:
    int _mosfetPowerPin;
    int speed;
public:
    MOSFET_IRF520(int inputPin);
    ~MOSFET_IRF520();
    void setSpeed(int amount);
    int getSpeed();
};

MOSFET_IRF520::MOSFET_IRF520(int inputPin)
{
    _mosfetPowerPin = inputPin;
}

MOSFET_IRF520::~MOSFET_IRF520()
{
}

void MOSFET_IRF520::setSpeed(int amount)
                                        {
                                            speed = amount;
                                            digitalWrite(_mosfetPowerPin, amount);
                                        }

int MOSFET_IRF520::getSpeed()
                            {
                                return speed;
                            }
