/*
This library has been made to easily interface and use the DS3231 RTC with an Arduino or
chipKit. The library will also work with the DS3232 RTC chip but you will not be able to use
the internal SRAM.
This library will default to I2C Fast Mode (400 KHz) when using the hardware I2C interface.
The library has not been tested in combination with the Wire library and I have no idea if
they can share pins. Do not send me any questions about this. If you experience problems with
pin-sharing you can move the DS3231/DS3232 SDA and SCL pins to any available pins on your
development board. This library will in this case fall back to a software-based, TWI-/I2C-like
protocol which will require exclusive access to the pins used.
I highly recommend using the DS3231 (or DS3232) instead of the DS1307. While the DS3231/DS3232
may be slightly more expensive than the DS1307 it is much more accurate due to the internal
TCXO (temperature-compensated crystal oscillator) and crystal. This also means that you don’t
have to use an external crystal like you have to with the DS1307.
If you are using a chipKit Uno32 or uC32 and you want to use the hardware I2C interface you
2must remember to set the JP6 and JP8 jumpers to the I C position (closest to the analog pins).

From the DS3231 datasheet:

2The DS3231 is a low-cost, extremely accurate I C realtime clock (RTC) with an
integrated temperaturecompensated crystal oscillator (TCXO) and crystal. The
device incorporates a battery input, and maintains accurate timekeeping when main
power to the device is interrupted. The integration of the crystal resonator
enhances the long-term accuracy of the device as well as reduces the piece-part
count in a manufacturing line. The DS3231 is available in commercial and
industrial temperature ranges, and is offered in a 16-pin, 300-mil SO package.
The RTC maintains seconds, minutes, hours, day, date, month, and year
information. The date at the end of the month is automatically adjusted for
months with fewer than 31 days, including corrections for leap year. The clock
operates in either the 24-hour or 12-hour format with an AM/PM indicator. Two
programmable time-of-day alarms and a programmable square-wave output are
provided. Address and data are transferred serially through an I2C bidirectional
bus.
A precision temperature-compensated voltage reference and comparator circuit
monitors the status of VCC to detect power failures, to provide a reset output,
and to automatically switch to the backup supply when necessary. Additionally,
the RST pin is monitored as a pushbutton input for generating a μP reset.

http://www.RinkyDinkElectronics.com/

*/


#include "extLib/DS3231/DS3231.h"
#include "board/pinDefinition_Mega2560.h"
#include "Arduino.h"

DS3231  rtc(SDA, SCL);

class clockDS
{
private:
    //
    Time t;
    bool isClockStarted = false;
    bool is32kenable = false;
public:
    clockDS(/* args */);
    ~clockDS();
    void clockStart();
    String getTime();
    String getTimeString(bool shortFormat = false);
    String getDate(int yearShort = 4,int internationalFormat = 3, char divider = '.');
    String getTemperature();
    String getDayOfTheWeek(bool shortFormat);
    void setTime(int _hour, int _minute, int _second);
    void setDate(int _day, int _month, int _year);
    void setDow(int _dayOfTheWeek);
    void enable32K(bool state);
    bool get32kState();
    void setOutputSignal(bool trueForSquareFalseForInt);
    void setSquareRate(int rate);
};

clockDS::clockDS(/* args */)
{
}

clockDS::~clockDS()
{
}

void clockDS::clockStart()
                            {
                                //DS3231 rtc(SDA, SCL);
                                rtc.begin();
                                rtc.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY
                                rtc.setTime(00, 25, 0);     // Set the time to 12:00:00 (24hr format)
                                rtc.setDate(2, 1, 2021);
                                isClockStarted = true;
                                Serial.println("clockStarted");
                            }

String clockDS::getTime()
                            {
                                if (!isClockStarted)
                                {
                                    clockStart();
                                }
                                
                                t = rtc.getTime();
                                String returnString = String(t.hour)+":"+String(t.min)+":"+String(t.sec);
                                Serial.println(returnString);
                                return returnString;
                            }
String clockDS::getTimeString(bool shortFormat /*= false*/)
                                {
                                    /*
                                    Get current time as a string.
                                    Parameters:
                                    format: <Optional>
                                    FORMAT_LONG "hh:mm:ss"
                                    (default)
                                    FORMAT_SHORT "hh:mm"
                                    Returns:
                                    String containing the current time with or without seconds.
                                    Usage:
                                    Serial.print(rtc.getTimeStr()); // Send the current time over a serial connection

                                    */
                                   t = rtc.getTime();
                                    if (!isClockStarted)
                                                        {
                                                            clockStart();
                                                        }
                                    String returnString = rtc.getTimeStr(shortFormat);
                                    return returnString;
                                }
String clockDS::getDate(int yearShort,int internationalFormat, char divider )
                            {
                                if (!isClockStarted)
                                {
                                    clockStart();
                                }
                                /*
                                        Get current date as a string.
                                getDateStr([slformat[, eformat[, divider]]]);
                                Parameters:     slformat: <Optional> *1
                                                        FORMAT_LONG Year with 4 digits (yyyy) (default)
                                                        FORMAT_SHORT Year with 2 digits (yy)
                                                eformat: <Optional> *2
                                                        FORMAT_LITTLEENDIAN "dd.mm.yyyy" (default)
                                                        FORMAT_BIGENDIAN "yyyy.mm.dd"
                                                        FORMAT_MIDDLEENDIAN "mm.dd.yyyy"
                                                divider: <Optional>
                                                        Single character to use as divider. Default is '.'

                                Returns:        String containing the current date in the specified format.

                                Usage:          Serial.print(rtc.getDateStr()); // Send the current date over a serial
                                                
                                Notes:          *1: Required if you need eformat or divider.
                                                *2: Required if you need divider. More information on Wikipedia
                                                (http://en.wikipedia.org/wiki/Date_format#Date_format).
                                */
                                t = rtc.getTime();
                                String returnString = rtc.getDateStr(yearShort,internationalFormat,divider);
                                Serial.println(returnString);
                                return returnString;
                            }
String clockDS::getTemperature()
                                {
                                    if (!isClockStarted)
                                                        {
                                                            clockStart();
                                                        }
                                    // la misura della temperatura viene fatta ogni 64 secondi
                                    String returnString = "T000 C"+ String(rtc.getTemp());
                                    return returnString;
                                }
String clockDS::getDayOfTheWeek(bool shortFormat)
                                {
                                    /*
                                                    Get current day-of-the-week as a string.
                                    Parameters:     format: <Optional>
                                                        FORMAT_LONG Day-of-the-week in English (default)
                                                        FORMAT_SHORT Abbreviated Day-of-the-week in English (3 letters)

                                    Returns:        String containing the current day-of-the-week in full or abbreviated format.

                                    Usage:          Serial.print(rtc.getDOWStr(FORMAT_SHORT)); // Send the current day in abbreviated format over a serial connection


                                    */
                                    if (!isClockStarted)
                                                        {
                                                            clockStart();
                                                        }
                                    // la misura della temperatura viene fatta ogni 64 secondi
                                    String returnString = "Clock I:"+ String(rtc.getDOWStr(FORMAT_SHORT));
                                    if (!shortFormat)
                                                    {
                                                        returnString = "Clock I:"+ String(rtc.getDOWStr(FORMAT_LONG));
                                                    }
                                    return returnString;
                                }

void clockDS::setTime(int _hour, int _minute, int _second)
                                                        {
                                                            /*
                                                            Set the time.
                                                            Parameters:
                                                                            hour: Hour to store in the DS3231 (0-23)
                                                                            min:  Minute to store in the DS3231 (0-59)
                                                                            sec:  Second to store in the DS3231 (0-59)
                                                            Returns:        Nothing
                                                            Usage:          rtc.setTime(23, 59, 59); // Set the time to 23:59:59
                                                            */
                                                        rtc.setTime(_hour,_minute,_second);
                                                        Serial.print("set new time: ");
                                                        getTimeString();
                                                        Serial.println("####################");
                                                        }
void clockDS::setDate(int _day, int _month, int _year)
                                                        {
                                                            /*
                                                            Set the date.
                                                            Parameters:
                                                                            date:   Date of the month to store in the DS3231 (1-31) *1
                                                                            mon:    Month to store in the DS3231 (1-12)
                                                                            year:   Year to store in the DS3231 (2000-2099)

                                                            Returns:        Nothing
                                                            Usage:          rtc.setDate(4, 7, 2014); // Set the date to July 4th 2014.
                                                            Notes:          *1: No checking for illegal dates so Feb 31th is possible to input. The effect of doing this is unknown.
                                                            */
                                                        rtc.setTime(_day,_month,_year);
                                                        Serial.print("set new date: ");
                                                        getDate();
                                                        Serial.println("####################");
                                                        }
void clockDS::setDow(int _dayOfTheWeek)
                                        {
                                            /*
                                            Set the date.
                                            Parameters:
                                                            date:   Date of the month to store in the DS3231 (1-31) *1
                                                            mon:    Month to store in the DS3231 (1-12)
                                                            year:   Year to store in the DS3231 (2000-2099)

                                            Returns:        Nothing
                                            Usage:          rtc.setDate(4, 7, 2014); // Set the date to July 4th 2014.
                                            Notes:          *1: No checking for illegal dates so Feb 31th is possible to input. The effect of doing this is unknown.
                                            */
                                        switch (_dayOfTheWeek)
                                                                {
                                                                case 1:
                                                                    /* code */
                                                                    rtc.setDOW(MONDAY);
                                                                    break;
                                                                case 2:
                                                                    rtc.setDOW(TUESDAY);
                                                                    break;
                                                                case 3:
                                                                    rtc.setDOW(WEDNESDAY);
                                                                    break;
                                                                case 4:
                                                                    rtc.setDOW(THURSDAY);
                                                                    break;
                                                                case 5:
                                                                    rtc.setDOW(FRIDAY);
                                                                    break;
                                                                case 6:
                                                                    rtc.setDOW(SATURDAY);
                                                                    break;
                                                                case 7:
                                                                    rtc.setDOW(SUNDAY);
                                                                    break;
                                                                
                                                                default:
                                                                    rtc.setDOW();
                                                                    break;
                                                                }
                                        
                                        Serial.print("set new day of the week: ");
                                        getDayOfTheWeek(false);
                                        Serial.println("####################");
                                        }

void clockDS::enable32K(bool state)
                                    {
                                        rtc.enable32KHz(state);
                                        is32kenable = state;
                                    }
bool clockDS::get32kState()
                            {
                                return is32kenable;
                            }
void clockDS::setOutputSignal(bool trueForSquareFalseForInt)
                                                            {
                                                                if (trueForSquareFalseForInt)
                                                                {
                                                                    rtc.setOutput(OUTPUT_SQW);
                                                                }
                                                                else
                                                                {
                                                                    rtc.setOutput(OUTPUT_INT);
                                                                }
                                                            }
void clockDS::setSquareRate(int rate)
                                     {
                                         /*
                                         Set the Square Wave output rate if the INT/SQW pin is set to output SQW.

                                            Parameters:     SQW_RATE_1   sets a 1Hz rate
                                                            SQW_RATE_1K  sets a 1.024Hz rate
                                                            SQW_RATE_4K  sets a 4.096Hz rate
                                                            SQW_RATE_8K  sets a 8.192Hz rate

                                            Return:         nothing
                                            Usage:          rtc.setSQWRate(SQW_RATE_1); // Sets the rate for SQW to 1 Hz
                                         */
                                        switch (rate)
                                                    {
                                                    case 1:
                                                        rtc.setSQWRate(SQW_RATE_1);
                                                        break;
                                                    case 2:
                                                        rtc.setSQWRate(SQW_RATE_1K);
                                                        break;
                                                    case 3:
                                                        rtc.setSQWRate(SQW_RATE_4K);
                                                        break;
                                                    case 4:
                                                        rtc.setSQWRate(SQW_RATE_8K);
                                                        break;
                                                    default:
                                                        Serial.println("Please select a range from 1-4 ex: 1 = 1Hz, 2 = 1.024Khz, 3 = 4.096Khz, 4 = 8.192 Khz");
                                                        break;
                                                    }
                                     }