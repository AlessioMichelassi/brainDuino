/*
Il DHT11 è un sensore digitale di umidità e temperatura dell’aria 
costituito da una parte resistiva che si occupa della rilevazione 
dell’umidità e da un NTC che rileva la temperatura, 
queste due parti sono gestite da un microcontrollore che è parte integrante del sensore. 
Il DHT 11 viene pre-calibrato in fabbrica e i dati di calibrazione vengono memorizzati 
all’interno di una memoria di sola lettura (OPT Memory).


    Intervallo di temperatura: da 0 a 50 ºC +/-2 ºC
    Intervallo di umidità: da 20 a 90% +/-5%
    Risoluzione:
        Umidità: 1%
        Temperatura: 1ºC
    Tensione di alimentazione: 3 – 5.5 V DC
    Corrente assorbita: 0.5 – 2.5 mA
    Periodo di campionamento: 1 sec

Se la distanza fra il sensore e la scheda è inferiore a 2 metri
è consigliabile inserire una resistenza di pulldown di 4,7 Kohm

Se il componente è montato su scheda a 3 pin di solito la resistenza è già montata.

i pin sono Vcc signal e Gnd

https://www.maffucci.it/2019/10/03/arduino-utilizzo-del-sensore-di-umidita-e-temperatura-dht11/
*/


//
#include "DHT.h"
#include "Arduino.h"
#include "board/pinDefinition_Mega2560.h"

#define DHTPIN temperatureSensor1
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

class tempSensor_dht11
{
private:
    float humidity, temperatureCelsius, temperatureFahreneight;
public:
    
    tempSensor_dht11(/* args */);
    ~tempSensor_dht11();
    String getTemperature();
    void printDelay(int lapse);
    void startTempSensor(int lapse);
    void stopTempSensor();
};

tempSensor_dht11::tempSensor_dht11(/* args */)
                                                {
                                                    dht.begin();
                                                }

tempSensor_dht11::~tempSensor_dht11()
{
}
void tempSensor_dht11::printDelay(int lapse)
                                            {
                                                Serial.print("waiting ");
                                                for (int i = 0; i < lapse; i++)
                                                {
                                                    delay(100);
                                                    Serial.print(". ");
                                                }
                                                Serial.println(" - Done");
                                            }
String tempSensor_dht11::getTemperature()
{
    
    printDelay(20);
    // Per leggere umidità e temperatura il sensore impiega circa 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    humidity = dht.readHumidity();
    // Read temperature as Celsius (the default)
    temperatureCelsius = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    temperatureFahreneight = dht.readTemperature(true);
    if (isnan(humidity) || isnan(temperatureCelsius) || isnan(temperatureFahreneight)) 
                                                                                        {
                                                                                        Serial.println(F("Failed to read from DHT sensor!"));
                                                                                        return "failed";
                                                                                        }
    float heatIndex = dht.computeHeatIndex(temperatureCelsius, humidity, false);
    String returnString = ("H" + String(humidity) + ";C" + String(temperatureCelsius)+";P"+String(heatIndex));
    return returnString;
}

void tempSensor_dht11::startTempSensor(int lapse)
{
}

void tempSensor_dht11::stopTempSensor()
{
}
