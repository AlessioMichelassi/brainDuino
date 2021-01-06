#include "Arduino.h"
#include "board/pinDefinition_Mega2560.h"

class Mega2560SetUp
                    {
                    private:
                        /* data */
                    public:
                        Mega2560SetUp(/* args */);
                        ~Mega2560SetUp();
                        void setPin();
                    };


Mega2560SetUp::Mega2560SetUp(/* args */)
{
    setPin();
}

Mega2560SetUp::~Mega2560SetUp()
{
}

void Mega2560SetUp::setPin()
{
    //pinMode(genPin1, OUTPUT);
    
        // Generalmente questo pin è associato al lettore di temperatura interno
    //pinMode(genPin2, OUTPUT);
    
        // pin collegato al buzzer
        pinMode(buzzerPin, OUTPUT);
    //pinMode(genPin4, OUTPUT);
    //pinMode(genPin5, OUTPUT);
    //pinMode(genPin6, OUTPUT);
    //pinMode(genPin7, OUTPUT);

        // Questo pin E' collegato al relay generale che alimenta la board

    pinMode(mainPower, OUTPUT); //pin8

        // Quando vengono premuti i pulsanti vengono accesi i led collegati
        // a questi pin

    pinMode(iLedPin1, OUTPUT); //pin9
    pinMode(iLedPin2, OUTPUT); //pin10
    pinMode(iLedPin3, OUTPUT); //pin11
    pinMode(iLedPin4, OUTPUT); //pin12
    
    pinMode(ledBuiltIn, OUTPUT); //LedBuiltIn 

    //pinMode(genPin14, OUTPUT);
    //pinMode(genPin15, OUTPUT);
    //pinMode(genPin16, OUTPUT);
    //pinMode(genPin17, OUTPUT);
    //pinMode(genPin18, OUTPUT);
    //pinMode(genPin19, OUTPUT);
    //pinMode(genPin20, OUTPUT);
    //pinMode(genPin21, OUTPUT);


    //      ################### THIS IS CONNECTED TO THE RELAY 4 CH MODULE
    pinMode(relaych1, OUTPUT);  //pin22
    pinMode(relaych2, OUTPUT);  //pin23
    pinMode(relaych3, OUTPUT);  //pin24
    pinMode(relaych4, OUTPUT);  //pin25
    
    
    //      ################### THIS IS CONNECTED TO THE RELAY 4 PUSHBUTTON
    pinMode(pushBtn1, INPUT); //pin26
    pinMode(pushBtn2, INPUT); //pin27
    pinMode(pushBtn3, INPUT); //pin28
    pinMode(pushBtn4, INPUT); //pin29
    
    
    //pinMode(genPin30, OUTPUT);
    //pinMode(genPin31, OUTPUT);
    //pinMode(genPin32, OUTPUT);
    //pinMode(genPin33, OUTPUT);
    //pinMode(genPin34, OUTPUT);
    //pinMode(genPin35, OUTPUT);
    //pinMode(genPin36, OUTPUT);
    //pinMode(genPin37, OUTPUT);
    //pinMode(genPin38, OUTPUT);
    //pinMode(genPin49, OUTPUT);
    //pinMode(genPin40, OUTPUT);
    //pinMode(genPin41, OUTPUT);
    //pinMode(genPin42, OUTPUT);
    //pinMode(genPin43, OUTPUT);
    //pinMode(genPin44, OUTPUT);
    //pinMode(genPin45, OUTPUT);
    //pinMode(genPin46, OUTPUT);
    //pinMode(genPin47, OUTPUT);
    //pinMode(genPin48, OUTPUT);
    //pinMode(genPin49, OUTPUT);
    //pinMode(genPin50, OUTPUT);
    //pinMode(genPin51, OUTPUT);

        // This pin is used for reset the boad
    pinMode(resetBoard, OUTPUT);
}