#include "Arduino.h"
#include "core/GCode.h"

class serialInterpreter
{
private:
    GCode gCode;
    bool verboseDebug = true;
    bool isIntervalSerialDebounce = true;
    unsigned const long intervalSerialDebounce = 1000;
    unsigned long currentMillis = millis();
    unsigned long previousMillis = intervalSerialDebounce;
    String lastMessage = "";
    String tokenizedString[18];
public:
    serialInterpreter(/* args */);
    ~serialInterpreter();
    void setVerboseSerialDebug(bool state);
    void setIntervalSerialDebounce(bool state);
    bool getIntervalSerialDebounce();
    void tokenizeString(String rxMsg);
    void printTokenizeString();
    void analizeToken(String token[18]);
};

serialInterpreter::serialInterpreter(/* args */)
{
}

serialInterpreter::~serialInterpreter()
{
}

void serialInterpreter::setVerboseSerialDebug(bool state)
{
    verboseDebug = state;
    if (state)
            {
                Serial.println("Serial Verbose Debug Active");
                gCode.setVerboseSerialDebug(true);
            }
    else
        {
            Serial.println("Serial Verbose Debug Not Active");
            gCode.setVerboseSerialDebug(false);
        }
    
}

/*
    Se i comandi vengono mandati in maniera ripetuta via seriale vengono ignorati
    e viene preso in considerazione solo il primo segnale
    Si può impostare un intervallo di 1 sec in modo da poter ripetere lo stesso comando più volte.
    La cosa può risultare comoda per sensori tipo temperatura o luce
*/
void serialInterpreter::setIntervalSerialDebounce(bool state)
                                                            {
                                                                isIntervalSerialDebounce = state;
                                                            }

bool serialInterpreter::getIntervalSerialDebounce()
                                                    {
                                                        return isIntervalSerialDebounce;
                                                    }
// 100 - Serial interpreter - tokenize String
/* Questa funzione raccoglie il messaggio e lo divide in un array
    suddividendolo nei vari codici. Il comando che si aspetta di ricevere
    è del tipo: M150 I1 P255
    dome M è il tipo di comando
    I è l'indirizzo del tool
    P è il grado di potenza che deve essere generato 0 per off, 255 full on
    se è collegato un mosfet la potenza in uscita dal pin può essere variata con dei valori da 0 a 255
    I token vengono separati usando gli spazi. Se fra due comandi non è presente una spazio il comando non viene riconosciuto
    se nella frase non ci sono almeno 3 token il comando viene scartato
*/
void serialInterpreter::tokenizeString(String rxMsg)
                                                    {
                                                        currentMillis = millis(); // fa partire un cronometro
                                                        //Se il messaggio in arrivo è vuoto viene scartato
                                                        //così come se il messaggio in arrivo è uguale ad uno precedentemente inviato
                                                        if (rxMsg.length() > 0)
                                                                                {
                                                                                    if (isIntervalSerialDebounce)
                                                                                    {
                                                                                        // Se il comando viene ricevuto dopo 1sec dal precedente
                                                                                        if (currentMillis - previousMillis >= intervalSerialDebounce)
                                                                                        {
                                                                                            lastMessage = "";
                                                                                            previousMillis = currentMillis;
                                                                                        }
                                                                                        // altrimenti setta il tempo preso dal cronometro
                                                                                        else
                                                                                        {
                                                                                            previousMillis = millis();
                                                                                        }
                                                                                        
                                                                                    }
                                                                                    
                                                                                    if (rxMsg != lastMessage)
                                                                                                                {
                                                                                                                    
                                                                                                                    //La modalità verbosa analizza passo passo le varie funzioni 
                                                                                                                    if (verboseDebug)
                                                                                                                                    {
                                                                                                                                        Serial.println("FROM SERIAL INTERPRETER - TOKENIZE STRING");
                                                                                                                                        Serial.println("Tokenize incoming string.");
                                                                                                                                        Serial.print("echo: ");
                                                                                                                                        Serial.println(rxMsg);
                                                                                                                                        Serial.println("##############");
                                                                                                                                        Serial.println("\n\n");
                                                                                                                                    } //if (verboseDebug)
                                                                                                                    /*
                                                                                                                        la stringa arriva nel formato:
                                                                                                                        G1 E255 \n
                                                                                                                        per analizzarla bisogna creare due indici
                                                                                                                        uno per il carattere da cui partire
                                                                                                                        e uno che è dato dalla posizione dello spazio
                                                                                                                        prima del comando successivo
                                                                                                                    */
                                                                                                                    int m = 0;
                                                                                                                    int n = rxMsg.indexOf(" ");
                                                                                                                    int counter = 0;
                                                                                                                    // continua a cercare spazi nella stringa fino a che while
                                                                                                                    // non trovando più spazi ritorna dichiara n =-1 e esce dal ciclo
                                                                                                                    while (n > 0)
                                                                                                                                {
                                                                                                                                    if (counter > 18)
                                                                                                                                                    {
                                                                                                                                                        Serial.println("there is a problem with the incoming message.");
                                                                                                                                                        Serial.println(rxMsg);
                                                                                                                                                        Serial.println("has too much character");
                                                                                                                                                        break;
                                                                                                                                                    }
                                                                                                                                    else
                                                                                                                                        {
                                                                                                                                            tokenizedString[counter] = rxMsg.substring(n,m);
                                                                                                                                            m = n+1;
                                                                                                                                            n = rxMsg.indexOf(" ", n+1);
                                                                                                                                            counter++;
                                                                                                                                        }
                                                                                                                                }//while (n > 0)
                                                                                                                    
                                                                                                                    if (tokenizedString[2] == "")
                                                                                                                                                {
                                                                                                                                                    Serial.println("command not recognized.");
                                                                                                                                                    if (verboseDebug)
                                                                                                                                                                    {
                                                                                                                                                                        Serial.println("the tokenized array at index 1 is empty.");
                                                                                                                                                                        Serial.print("first token: ");
                                                                                                                                                                        Serial.print(tokenizedString[0]);
                                                                                                                                                                        Serial.print("second token: ");
                                                                                                                                                                        Serial.print(tokenizedString[1]);
                                                                                                                                                                        Serial.print("third token: ");
                                                                                                                                                                        Serial.print(tokenizedString[2]);
                                                                                                                                                                    }
                                                                                                                                                    
                                                                                                                                                }
                                                                                                                    else
                                                                                                                        {
                                                                                                                            analizeToken(tokenizedString);
                                                                                                                        }
                                                                                                                lastMessage = rxMsg;
                                                                                                                rxMsg = "";
                                                                                                                }// end if(rxMsg != lastMessage)
                                                                                }//end if (rxMsg.length() > 0)
                                                    }// end function tokenizeString

void serialInterpreter::printTokenizeString()
                                            {
                                                int tokenLegth = tokenizedString->length();

                                                Serial.println("tokenized string result:");
                                                for (int i = 0; i < tokenLegth; i++)
                                                                                    {
                                                                                        Serial.print(i);
                                                                                        Serial.print(" - ");
                                                                                        Serial.println(tokenizedString[i]);
                                                                                    }
                                                Serial.println("##################\n\n");
                                            } //end function printTokenizedString

void serialInterpreter::analizeToken(String token[])
                                                    {
                                                        /*
                                                        Un comando può essere M(codice comando)
                                                        seguito dall'indirizzo del tool
                                                        seguito dalla potenza (esempio: 0-OFF..255-FULL ON)
                                                        */
                                                        //memset(tokenizedString, 0, sizeof(tokenizedString));
                                                        char command = tokenizedString[0].charAt(0);
                                                        int value = tokenizedString[0].substring(1,4).toInt();
                                                        char address = tokenizedString[1].charAt(0);
                                                        int addrValue = tokenizedString[1].substring(1,4).toInt();
                                                        char power = tokenizedString[2].charAt(0);
                                                        int powerValue = tokenizedString[2].substring(1,4).toInt();

                                                                                                            
                                                        gCode.doThis(command,value,address,addrValue, power,powerValue);
                                                        
                                                        /* //clear the array
                                                        int arrayLenght = tokenizedString->length();
                                                        for (int i = 0; i < arrayLenght; i++)
                                                                                            {
                                                                                                tokenizedString[i] = "";
                                                                                            } */
                                                    }//end function analizeToken
