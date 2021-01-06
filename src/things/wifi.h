#include <SoftwareSerial.h>
#include <Arduino.h>

   #define SSID "xxxxxxxx"
   #define PASS "xxxxxxxx"
   #define DST_IP "220.181.111.85" //baidu.com
   SoftwareSerial dbgSerial(10, 11); // RX, TX

class wifi
{
private:
    /* data */
public:
    wifi(/* args */);
    ~wifi();
    void wiFiStart();
};

wifi::wifi(/* args */)
{
}

wifi::~wifi()
{
}

void wifi::wiFiStart()
{
    dbgSerial.begin(9600); //can't be faster than 19200 for softserial
    dbgSerial.println("ESP8266 Demo");
     //test if the module is ready
    Serial.println("AT+RST");
    delay(1000);
    if(Serial.find("ready"))
                            {
                                dbgSerial.println("Module is ready");
                            }
    else
        {
            dbgSerial.println("Module have no response.");
            while(1);
        }
    delay(1000);

    //connect to the wifi
    bool connected=false;
    for(int i=0;i<5;i++)
                        {
                            //
                        }

    if (!connected){while(1);}

    delay(5000);

    //print the ip addr
    /*Serial.println("AT+CIFSR");
    dbgSerial.println("ip address:");
    while (Serial.available())
    dbgSerial.write(Serial.read());*/
    //set the single connection mode
    Serial.println("AT+CIPMUX=0");


}





