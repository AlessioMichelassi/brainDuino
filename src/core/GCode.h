#include "Arduino.h"
#include "things/led.h"
#include "things/tempSensor_dht11.h"
//#include <Wire.h>
#include "things/clockDS.h"
#include "things/Buzzer.h"

class GCode
{
private:
    ledComander ledz;       // gestione led
    tempSensor_dht11 tempZ; //Sensori di temperatura
    String tempReaded = "";
    clockDS clockZ;
    Buzzer buzZ;

    String tempClock = "";
    bool verboseDebug = true;
public:
    GCode(/* args */);
    ~GCode();
 
    void setVerboseSerialDebug(bool);
    void doThis(char command, int value, char address, int value2, char power, int value3, char opt = 'x', int value4 = 0);
};

GCode::GCode(/* args */)
{
}

GCode::~GCode()
{
}

void GCode::setVerboseSerialDebug(bool state)
{
    verboseDebug = state;
    if (state)
            {
                Serial.println("Serial Verbose Debug Active");
                ledz.setVerboseSerialDebug(true);
            }
    else
        {
            Serial.println("Serial Verbose Debug Not Active");
            ledz.setVerboseSerialDebug(false);
        }
    
}



void GCode::doThis(char command, int value, char address, int value2, char power, int value3, char opt, int value4)
{
    if (verboseDebug)
                        {
                            Serial.println("FROM G-CODE - DO THIS");
                            Serial.println("command received");
                            Serial.print("command: ");
                            Serial.println(command);
                            Serial.print("address: ");
                            Serial.println(address);
                            Serial.print("power: ");
                            Serial.println(power);
                            Serial.println("##############");
                            Serial.println("\n\n");
                        } //if (verboseDebug)

    if (command == 'M')
                        {
                            switch (value)
                                            {
                                                case 0:
                                                /* 0 - ferma tutto */
                                                if (verboseDebug)
                                                                {
                                                                    Serial.println("case M0 - StopAll");
                                                                }
                                                    break;
                                                case 1:
                                                    /* 1 - sleep */
                                                    if (verboseDebug)
                                                                {
                                                                    Serial.println("case M1 - Sleep");
                                                                }
                                                    break;
                                                case 80:
                                                    /* 80 - accende l'alimentatore */
                                                    if (verboseDebug)
                                                                {
                                                                    Serial.println("case M80 - Turn On The PowerSupply");
                                                                }
                                                    break;
                                                case 81:
                                                    /* 81 - spenge l'alimentatore */
                                                    if (verboseDebug)
                                                                {
                                                                    Serial.println("case M81 - Turn Off The PowerSupply");
                                                                }
                                                    break;
                                                case 105:
                                                    /* 105 - legge la temperatura */
                                                    if (verboseDebug)
                                                                {
                                                                    Serial.println("case M105 - Turn On/Off The Temp Reader at given address");
                                                                }
                                                    tempReaded = tempZ.getTemperature();
                                                    Serial.println(tempReaded);
                                                    break;
                                                case 106:
                                                    /* 106 - accende la ventola */
                                                    if (verboseDebug)
                                                                {
                                                                    Serial.println("case M106 - Turn On/Off The Fan at given address at given speed");
                                                                }
                                                    break;
                                                case 107:
                                                    /* 107 - spegne la ventola */
                                                    break;
                                                case 115:
                                                    /* 115 - visualizza la versione del firmware */
                                                    Serial.println("software Version");
                                                    Serial.println("firmwareVersion");
                                                    break;
                                                case 150:
                                                    /* 150 - comanda le luci led 
                                                    M150 [B<intensity>] [I<index>] [P<intensity>] [R<intensity>] [U<intensity>] [W<intensity>]
                                                    // per accendere un led si usa : led(ledPin,intensity)
                                                    // Se invece che da I il comando è seguito da B si cerca di comandare un led RGB
                                                    // per accendere un red RGB si usa: rgbLed(rPin,gPin,bPin,rIntensity,gIntensity,bIntensity)
                                                    // per accendere un red RGB-W si usa: rgbwLed(rPin,gPin,bPin,wPin,rIntensity,gIntensity,bIntensity,wIntensity)
                                                    */
                                                    if (verboseDebug)
                                                                    {
                                                                        Serial.println("case M150 - Turn On/Off The Led at given address with given amount");
                                                                    }
                                                    Serial.print("received: led ");
                                                    Serial.print(value2);
                                                    if (value3 == 0)
                                                                    {
                                                                        Serial.println(" off");   
                                                                    }
                                                    else if (value3 > 254)
                                                                            {
                                                                                Serial.println(" on");
                                                                                power = 255; 
                                                                            }
                                                    else
                                                        {
                                                            Serial.print(" on - at: ");
                                                            int percentage = (100 * value3)/255; 
                                                            Serial.print(percentage);
                                                            Serial.println(" %");
                                                        }
                                                    
                                                    
                                                    ledz.turnOn(value2, value3);
                                                    
                                                    break;

                                                case 155:
                                                    /* 155 - temperature auto report */
                                                    break;

                                                case 999:
                                                    /* 999 - reset di sistema */
                                                    break;

                                                default:
                                                Serial.println("command non recognize or not yet implemented");
                                                    break;
                                            }
                        }
    else if (command == 'S')
    {
        switch(value)
                        {
                        case 100:
                            /* 
                            set clock time
                            ex: S100 H20 M30  
                            */
                            clockZ.setTime(value2,value3,0);
                            break;
                        case 101:
                            /* 
                            set clock date
                            ex: S101 Y21 M01 D01  
                            */
                            clockZ.setDate(value2,value3,value4);
                            break;
                        case 102:
                            /* 
                            set day of the week
                            ex: S102 D1 ;for monday  
                            */
                            clockZ.setDow(value2);
                            break;
                        case 110:
                            /* 
                            Return the time clock  
                            */
                            tempClock = clockZ.getTime();
                            Serial.print("time clock: ");
                            Serial.println(tempClock);
                            break;
                        case 111:
                            /* 
                            Return the time Date  
                            */
                           tempClock = clockZ.getDate();
                           Serial.print("date: ");
                           Serial.println(tempClock);
                            break;
                        case 200:
                            /*
                            buzzer
                            */
                            buzZ.sbuzz();
                            break;
                        case 201:
                            /*
                            buzzer
                            */
                            buzZ.sbuzzRnd();
                            break;
                        default:
                            break;
                        }
    }
    
    
    
    
}
