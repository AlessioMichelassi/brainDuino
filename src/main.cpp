#include <Arduino.h>
#include "board/board.Mega2560.h"
#include "core/serialInterpreter.h"
#include "things/pushButtnon.h"

#include <Wire.h>


Mega2560SetUp arduBrain;
serialInterpreter serialZ;
pushButton btnZ;



String receivedMessage = "";
bool incomingDataComplete = false;


void setup() 
            {
              arduBrain.setPin();
              
              Serial.begin(115200);
              receivedMessage.reserve(200);
              serialZ.setVerboseSerialDebug(true); //Activate Verbose serial debug
              while(!Serial)
                            {
                              Serial.print(".");
                            }
              //DateTime now = RTC.now();
              Wire.begin();
              
            }

void checkSerial()
                  {
                    if (incomingDataComplete) 
                                            {
                                              Serial.println("message received");
                                              serialZ.setVerboseSerialDebug(true);
                                              serialZ.tokenizeString(receivedMessage);
                                              receivedMessage = "";
                                              incomingDataComplete = false;
                                            }
                  }

void checkButton()
                  {
                    String chkBtn = btnZ.checkState();
                    if (chkBtn != "")
                    {
                      serialZ.tokenizeString(chkBtn);
                    }
                    
                  }

void serialEvent() 
                  {
                  while (Serial.available()) 
                                              {
                                                  // get the new byte:
                                                  char inChar = (char)Serial.read();
                                                  // add it to the inputString:
                                                  receivedMessage += inChar;
                                                  // if the incoming character is a newline, set a flag so the main loop can
                                                  // do something about it:
                                                  if (inChar == '\n') 
                                                                      {
                                                                        receivedMessage += " ";
                                                                        incomingDataComplete = true;
                                                                      }
                                              }
                  }


void loop() 
          {
            checkSerial();
            checkButton();
          }


