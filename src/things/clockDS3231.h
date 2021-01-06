#include <Arduino.h>
#include <Wire.h>
#include "DS3231.h"



class clockDS3231
{
private:

    DS3231 clock;
    bool Century = false;
    bool h12;
    bool PM;
    String hour, minute, second, day, month, year;
    byte Hour, Minute, Second, DoW, Date, Month, Year;
public:
    clockDS3231(/* args */);
    ~clockDS3231();
    void setTime(int _hour, int _minute, int _second);
    void setHour(int _hour);
    void setMinute(int _minute);
    void setSecond(int _second);
    String getTime();
    void setDay(int _day);
    String getDay();
    void setMonth(int _month);
    String getMonth();
    void setYear(int _year);
    String getYear();
    String getDate();
    void setDate(int _year,int _month,int _day);
    void setClockMode(bool state);
    void setDow(int dayOfTheweek);
};

clockDS3231::clockDS3231(/* args */)
{
    
}

clockDS3231::~clockDS3231()
{
}

void clockDS3231::setHour(int _hour)
                                    {
                                        clock.setHour(byte(_hour));
                                        Serial.println("echo: clock set hour ");
                                        Serial.println(_hour);
                                    }
void clockDS3231::setMinute(int _minute)
                                        {
                                            clock.setHour(byte(_minute));
                                            Serial.println("echo: clock set minute ");
                                            Serial.println(_minute);
                                        }
void clockDS3231::setSecond(int _second)
                                        {
                                            clock.setHour(byte(_second));
                                            Serial.println("echo: clock set hour ");
                                            Serial.println(_second);
                                        }
void clockDS3231::setTime(int _hour, int _minute, int _second)
                                                                {
                                                                    clock.setHour(byte(20));
                                                                    clock.setHour(byte(_minute));
                                                                    clock.setHour(byte(_second));
                                                                    String newTime = String(_hour) + ":" + String(_minute) + ":" + String(_second);
                                                                    Serial.print("echo: set new time - ");
                                                                    Serial.println(getTime());
                                                                }
void clockDS3231::setDay(int _day)
                                    {
                                        clock.setDate(byte(_day));
                                        Serial.println("echo: clock set day ");
                                        Serial.println(_day);
                                    }
void clockDS3231::setMonth(int _month)
                                        {
                                            clock.setMonth(byte(_month));
                                            Serial.println("echo: clock set month ");
                                            Serial.println(_month);
                                        }
void clockDS3231::setYear(int _year)
                                        {
                                            clock.setYear(byte(_year));
                                            Serial.println("echo: clock set year ");
                                            Serial.println(_year);
                                        }   
void clockDS3231::setDate(int _year,int _month,int _day)
                                                        {
                                                            clock.setYear(byte(_year));
                                                            clock.setMonth(byte(_month));
                                                            clock.setDate(byte(_day));
                                                            String newDate = String(_year) + ":" + String(_month) + ":" + String(_day);
                                                            Serial.print("echo: set new Date - ");
                                                            Serial.println(newDate);
                                                        }                                      
void clockDS3231::setClockMode(bool state)
                                            {
                                                clock.setClockMode(state);
                                            }

String clockDS3231::getTime()
                            {
                                bool h12 = true;
                                bool PM = true;
                                hour = String(clock.getHour(h12, PM));
                                minute = String(clock.getMinute());
                                second = String(clock.getSecond());
                                String time = hour +":"+minute+":"+ second;
                                Serial.println(time);
                                return String(time);
                            }
String clockDS3231::getDay()
                            {
                                day = clock.getDate();
                                return String(day);
                            }
String clockDS3231::getMonth()
                            {
                                month = clock.getMonth(Century);
                                return String(month);
                            }  
String clockDS3231::getYear()
                            {
                                year = clock.getYear();
                                return String(year);
                            } 
String clockDS3231::getDate()
                            {
                                day = clock.getDate();
                                month = clock.getMonth(Century);
                                year = clock.getYear();
                                return String(day) + ":"+String(month)+":"+String(year);
                            } 
void clockDS3231::setDow(int dayOfTheweek)
                                        {
                                            clock.setDoW(byte(dayOfTheweek));
                                            Serial.println("echo: day Of The week ");
                                            Serial.println(dayOfTheweek);
                                        } 