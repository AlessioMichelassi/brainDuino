#ifndef relayControl_h
#define relayControl_h
#include "Arduino.h"
#include "board/pinDefinition_Mega2560.h"



class relayControl
                    {
                        private:
                            // This include all private variale
                            int relayPin[4] = {relaych1,relaych2,relaych3,relaych4};
                            int relayLedPin[4] = {iLedPin1,iLedPin2,iLedPin3,iLedPin4};
                            int relayState[4] = {HIGH,HIGH,HIGH,HIGH};
                            

                        public:
                                
                                 relayControl();
                            void initRelay();
                            void setRelayState(int whichRelay, bool state);
                            bool getRelayState(int whichRelay);
                            void testRelay(int flashAbout, int timeAmount);
                            void setAllOff();
                            void setAllOn();
                            void setRelay(int relayChannel, int state);
                            void invertRelayState(int relayChannel);
                    };

#endif

relayControl::relayControl()
                            {
                                setAllOff();
                            }


// Setta lo stato di uno dei quattro Relay
void relayControl::setRelayState(int relay, bool state)
                                                            {
                                                                if (state)
                                                                            {
                                                                                //RELAY IS ON
                                                                                relayState[relay] = LOW;
                                                                                digitalWrite(relayPin[relay], LOW);
                                                                                digitalWrite(relayLedPin[relay], HIGH);
                                                                            }
                                                                else
                                                                    {
                                                                        //RELAY IS ON
                                                                        relayState[relay] = HIGH;
                                                                        digitalWrite(relayPin[relay], HIGH);
                                                                        digitalWrite(relayLedPin[relay], LOW);
                                                                    }
                                                            }

/*
    This function do: esegue un test aprende e chiudendo i relay
*/
void relayControl::testRelay(int flashAbout, int timeAmount)
                                                            {
                                                                int counter = 0;
                                                                Serial.println("test relay - setAll OFF");
                                                                setAllOff();
                                                                //Test The Relay
                                                                for (int i = 0; i < flashAbout; i++)
                                                                                                        {
                                                                                                        Serial.print("test relay n° ");
                                                                                                        delay(200);
                                                                                                        Serial.println(counter);
                                                                                                        digitalWrite(relayPin[counter], LOW);
                                                                                                        delay(timeAmount);
                                                                                                        digitalWrite(relayPin[counter], HIGH);
                                                                                                        delay(timeAmount);
                                                                                                        if (counter < 3)
                                                                                                                        {
                                                                                                                            counter++;
                                                                                                                        }
                                                                                                        else
                                                                                                            {
                                                                                                                counter = 0;
                                                                                                            }
                                                                                                        
                                                                                                        }
                                                                
                                                            }

/*
    This function do: inizializza i 4 relay della schedina in base ai pin assegnati
*/
void relayControl::setAllOff()
                                {
                                    for (int i = 0; i < 4; i++)
                                                                {
                                                                    relayState[i] = HIGH;
                                                                    digitalWrite(relayPin[i],relayState[i]);
                                                                }
                                }
/*
    This function do: inizializza i 4 relay della schedina in base ai pin assegnati
*/
void relayControl::setAllOn()
                                {
                                    for (int i = 0; i < 4; i++)
                                                                {
                                                                    relayState[i] = LOW;
                                                                    digitalWrite(relayPin[i],relayState[i]);
                                                                }
                                }
/*
    This function do: inizializza i 4 relay della schedina in base ai pin assegnati
*/
void relayControl::setRelay(int relayChannel, int state)
                                                        {
                                                            relayState[relayChannel] = state;
                                                            digitalWrite(relayPin[relayChannel], relayState[relayChannel]);
                                                        }
/*
    This function do: inverte lo stato di un relay
*/
void relayControl::invertRelayState(int relayChannel)
                                                        {
                                                            relayState[relayChannel] = !relayState[relayChannel];
                                                            
                                                            digitalWrite(relayPin[relayChannel], relayState[relayChannel]);
                                                        }