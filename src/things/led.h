#ifndef led_h
#define led_h
#include "Arduino.h"
#include "relayControl.h"

class ledComander
                {
                    private:
                        // This include all private variale
                        const int internalLed = 13;
                        bool verboseDebug = true;
                        bool isInternalLedOn = false;
                        relayControl relayCTRL;
                    public:
                             ledComander();
                        void setVerboseSerialDebug(bool);
                        void initinternalLed();
                        void testLedBlinking(int flashAbout, int timeAmount);
                        void turnONTheBuiltinLed();
                        void turnOFFTheBuiltInLed();
                        void invertTheBuiltInLedState();
                        void turnOn(int ledPin, int amount);
                        void turnOff(int ledPin);
                };

#endif


ledComander::ledComander()
                        {
                            //this initialize the class
                        }

void ledComander::setVerboseSerialDebug(bool state)
{
    verboseDebug = state;
}


/*
/   Questa funzione inizializza il led di default
*/
void ledComander::initinternalLed()
                                {
                                    pinMode(internalLed, OUTPUT);
                                    isInternalLedOn = false;
                                }
/*
/   Questa funzione fa lampeggiare il led per un determinato numero di volte ad una determinata frequenza
*/
void ledComander::testLedBlinking(int flashAbout, int timeAmount)
                                                                {
                                                                    Serial.println("waiting for test complete:");
                                                                    for (int i = 0; i < flashAbout; i++)
                                                                                                            {
                                                                                                            digitalWrite(internalLed, HIGH);
                                                                                                            isInternalLedOn = true;
                                                                                                            Serial.print(" on ");
                                                                                                            delay(timeAmount);
                                                                                                            digitalWrite(internalLed, LOW);
                                                                                                            isInternalLedOn = false;
                                                                                                            delay(timeAmount);
                                                                                                            Serial.print(" off ");
                                                                                                            }
                                                                    Serial.println("");
                                                                    Serial.println("test complete!");
                                                                    
                                                                }
/*
/   Questa funzione accende il led
*/
void ledComander::turnONTheBuiltinLed()
                                        {
                                            digitalWrite(internalLed, HIGH);
                                            isInternalLedOn = true;
                                        }
/*
/   Questa funzione spegne il led
*/
void ledComander::turnOFFTheBuiltInLed()
                                        {
                                            digitalWrite(internalLed, LOW);
                                            isInternalLedOn = false;
                                        }
/*
/   Questa funzione inverte lo stato del led
*/
void ledComander::invertTheBuiltInLedState()
                                            {
                                                if (isInternalLedOn)
                                                            {
                                                                digitalWrite(internalLed,LOW);
                                                                isInternalLedOn = !isInternalLedOn;
                                                            }
                                                else
                                                    {
                                                        digitalWrite(internalLed,HIGH);
                                                                isInternalLedOn = !isInternalLedOn;
                                                    }
                                                
                                                
                                                digitalWrite(internalLed, LOW);
                                            }


void ledComander::turnOn(int _ledPin, int amount)
                                                {
                                                    int led = _ledPin-1;
                                                    if (verboseDebug)
                                                                    {
                                                                        Serial.println("\n VERBOSE CTRL FPR PUSH BUTTON");
                                                                        Serial.print("tun On/Off led: pin ");
                                                                        Serial.print(led);
                                                                        Serial.print(" - amount: ");
                                                                        Serial.println(amount);
                                                                        Serial.println("############");
                                                                        Serial.print("\n\n");
                                                                    }
                                                    if (amount > 0)
                                                                    {
                                                                        if (amount > 250)
                                                                                            {
                                                                                            if (verboseDebug)
                                                                                                            {
                                                                                                                Serial.print("activated: led pin ");
                                                                                                                Serial.print(_ledPin);
                                                                                                                Serial.println(" On");
                                                                                                            }
                                                                                            relayCTRL.setRelayState(led,true);
                                                                                            }
                                                                        else
                                                                            {
                                                                                // in questo controlla se in coda al relay c'è
                                                                                // un potenziometro e lo apre e lo chiude in base
                                                                                // alla quantità stabilita
                                                                                if (verboseDebug)
                                                                                                    {
                                                                                                    int percentage = (100 * amount)/255; 
                                                                                                    Serial.print("activated: led pin ");
                                                                                                    Serial.print(_ledPin);
                                                                                                    Serial.print(" On at ");
                                                                                                    Serial.print(percentage);
                                                                                                    Serial.println(" % ");
                                                                                                    }
                                                                                relayCTRL.setRelayState(led,true);
                                                                            }
                                                                    }
                                                    else // Se amount è Zero
                                                        {
                                                            relayCTRL.setRelayState(led,false);
                                                        }
                                    
                                                }

void ledComander::turnOff(int ledPin)
                                    {
                                        digitalWrite(ledPin,LOW);
                                    }
