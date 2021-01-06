#ifndef pushButton_h
#define pushButton_h
#include "Arduino.h"
#include "board/pinDefinition_Mega2560.h"

class pushButton
                {
                    private:

                        
                        int pushButtonPin[4] = {pushBtn1,pushBtn2,pushBtn3,pushBtn4};
                        int pushButtonState[4] = {LOW,LOW,LOW,LOW};
                        int lastPushButtonState[4] = {LOW,LOW,LOW,LOW};
                        unsigned long lastTimeBtnWasPressed = 0;

                        // This variable are for testing the function
                        int test_BtnState;             // the current reading from the input pin
                        int test_lastButtonState = LOW;
                        unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
                        unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
                        
                        bool isBtnPushed = false;
                        long timeBtnIsPushed,timeButtonisRelised;
                        bool verboseDebug = true;
                        
                            
                    public:
                             pushButton();
                        void setVerboseSerialDebug(bool);
                        void initpushButtonPin(int pin1, int pin2, int pin3, int pin4);
                        void test_checkState();
                        bool debounceState();
                        String checkState();
                        void checkPushing();
                };

#endif

pushButton::pushButton()
                        {
                            //this initialize the class
                        }

void pushButton::setVerboseSerialDebug(bool state)
{
    verboseDebug = state;
}

void pushButton::initpushButtonPin(int pin1, int pin2, int pin3, int pin4)
                                                                            {
                                                                                pushButtonPin[0] = pin1;
                                                                                pushButtonPin[1] = pin2;
                                                                                pushButtonPin[2] = pin3;
                                                                                pushButtonPin[3] = pin4;
                                                                                pinMode(pushButtonPin[0], INPUT);
                                                                                pinMode(pushButtonPin[1], INPUT);
                                                                                pinMode(pushButtonPin[2], INPUT);
                                                                                pinMode(pushButtonPin[3], INPUT);
                                                                                Serial.println("pushButton inited.");
                                                                            }

/*
    millis ritorna un numero che può essere usato come cronometro.
    nel caso in cui il pulsante viene premuto viene memorizzato.
    Se si preme il pulsante in un intervallo di tempo troppo breve la pressione viene ignorata
    Questo serve a prevenire che rumori elettrici sul circuito facciano cambiare lo stato dei pulsanti
*/
bool pushButton::debounceState()
                                {
                                    if ((millis() - lastTimeBtnWasPressed) > debounceDelay)
                                                                                            {
                                                                                                lastTimeBtnWasPressed = millis();
                                                                                                return true;
                                                                                            }
                                    return false;
                                }

void pushButton::checkPushing()
                                {

                                    if (pushButtonState[0] == HIGH && isBtnPushed == false)
                                                                                            {
                                                                                                isBtnPushed = true;
                                                                                                timeBtnIsPushed = millis(); //Fa partire il cronometro

                                                                                            }
                                    if(pushButtonState[0] == LOW && isBtnPushed == true)
                                                                                        {
                                                                                            isBtnPushed = false;
                                                                                            timeButtonisRelised = millis()-timeBtnIsPushed;
                                                                                            Serial.println("#############");
                                                                                            Serial.print("il pulsante è stato premuto per ");
                                                                                            Serial.print(String(timeButtonisRelised));
                                                                                            Serial.println(" s");
                                                                                            Serial.println("#############");
                                                                                        }
                                }

/*
    Questa funzione controlla senza debounce lo stato dei 4 pulsanti
    Nel caso in cui uno dei pulsanti venga premuto lo scrive sulla porta seriale
*/
String pushButton::checkState()
                                {
                                    String returnString = "";
                                    /*
                                        Questo ciclo controlla se uno dei 4 pulsanti è stato premuto
                                    */
                                    for (int i = 0; i < 4; i++)
                                                                {
                                                                    if (digitalRead(pushButtonPin[i]) == HIGH)
                                                                                                            {
                                                                                                                pushButtonState[i] = !pushButtonState[i];
                                                                                                                delay(200);
                                                                                                            }
                                                                }
                                    // Se la cosa è avvenuto dopo il tempo di debounce
                                    if(debounceState())
                                                    {
                                                        // controlla in base allo stato precedente se il pulsante è stato premuto per accendere o spegnere la luce
                                                        for (int i = 0; i < 4; i++)
                                                                                    {
                                                                                        if (pushButtonState[i] == HIGH && lastPushButtonState[i] == LOW)
                                                                                                                                                        {
                                                                                                                                                            String tempIndex = String(i+1);
                                                                                                                                                            returnString = "M150 I" + tempIndex + " P255 ";
                                                                                                                                                            if (verboseDebug)
                                                                                                                                                                            {
                                                                                                                                                                                Serial.print("button ");
                                                                                                                                                                                Serial.print(i);
                                                                                                                                                                                Serial.print(" ");
                                                                                                                                                                                Serial.println("pushBtn ON");
                                                                                                                                                                                Serial.println(returnString);
                                                                                                                                                                            }
                                                                                                                                                            lastPushButtonState[i] = pushButtonState[i];
                                                                                                                                                            delay(200);
                                                                                                                                                        }
                                                                                        else if (pushButtonState[i] == LOW && lastPushButtonState[i] == HIGH)
                                                                                                                                                            {
                                                                                                                                                                String tempIndex = String(i+1);
                                                                                                                                                                returnString = "M150 I" + tempIndex + " P0 ";
                                                                                                                                                                if (verboseDebug)
                                                                                                                                                                                {
                                                                                                                                                                                    Serial.print("button ");
                                                                                                                                                                                    Serial.print(i);
                                                                                                                                                                                    Serial.print(" ");
                                                                                                                                                                                    Serial.println("pushBtn OFF");
                                                                                                                                                                                    Serial.println(returnString);
                                                                                                                                                                                }
                                                                                                                                                                lastPushButtonState[i] = pushButtonState[i];
                                                                                                                                                                delay(200);
                                                                                                                                                            }
                                                                                    } // end For loop
                                                    }
                                    // ritorna la stringa da inviare al controller del g-Code
                                    return returnString;
                                }

