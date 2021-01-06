/*

https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/

    Il sensore a ultrasuoni HC-SR04 utilizza il sonar per determinare 
    la distanza da un oggetto come fanno i pipistrelli. 
    Offre un eccellente rilevamento della portata senza contatto con un'elevata precisione 
    e letture stabili in un pacchetto facile da usare. 
    Viene fornito completo di trasmettitore e modulo ricevitore ad ultrasuoni.

    Power Supply :+5V DC
    Quiescent Current : <2mA
    Working Current: 15mA
    Effectual Angle: <15°
    Ranging Distance : 2cm – 400 cm/1″ – 13ft
    Resolution : 0.3 cm
    Measuring Angle: 30 degree
    Trigger Input Pulse width: 10uS
    Dimension: 45mm x 20mm x 15mm

    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - sonarTriggerPin
        Echo: Echo (OUTPUT) - sonarEchoPin
        GND: GND


*/
#include "Arduino.h"

class sonar_HCSR04
{
private:
int _sonarTriggerPin, _sonarEchoPin;
    long duration, cm, inches;
public:
    sonar_HCSR04(int triggerPin, int echoPin);
    ~sonar_HCSR04();
    String getDistance();
};

sonar_HCSR04::sonar_HCSR04(int triggerPin, int echoPin)
{
    _sonarTriggerPin = triggerPin;
    _sonarEchoPin = echoPin;
}

sonar_HCSR04::~sonar_HCSR04()
{
}

String sonar_HCSR04::getDistance()
                                    {
                                        // Il sensore viene attivato da un impulso HIGH di 10 o più microsecondi.
                                        // Dare un breve impulso LOW in anticipo garantisce un impulso HIGH più pulito:
                                        digitalWrite(_sonarTriggerPin, LOW);
                                        delayMicroseconds(5);
                                        digitalWrite(_sonarEchoPin, HIGH);
                                        delayMicroseconds(10);
                                        digitalWrite(_sonarTriggerPin, LOW);
                                        /*  Legge il segnale dal sensore: un impulso HIGH la cui durata
                                            è il tempo (in microsecondi) dall'invio
                                            del ping alla ricezione della sua eco che rimbalza su qualche cosa. */

                                        duration = pulseIn(_sonarEchoPin, HIGH);
 
                                        // Convert the time into a distance
                                        cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
                                        inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
                                        
                                        
                                        String returnString = "distance: " + String(cm);
                                        delay(250);
                                    }