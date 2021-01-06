/*


Genera un'onda quadra della frequenza specificata 
(e del 50% del ciclo di lavoro) su un pin. 
È possibile specificare una durata, 
altrimenti l'onda continua fino a quando non viene chiamata noTone () . 
Il pin può essere collegato a un cicalino piezo o altro altoparlante per riprodurre i toni.

È possibile generare un solo tono alla volta. 
Se un tono è già riprodotto su un pin diverso, 
la chiamata a tone()non avrà effetto. S
e il tono viene riprodotto sullo stesso pin, la chiamata imposterà la sua frequenza.

L'utilizzo della tone()funzione interferirà 
con l'uscita PWM sui pin 3 e 11 (su schede diverse dalla Mega).

Non è possibile generare toni inferiori a 31Hz. 
Per i dettagli tecnici, vedere le note di Brett Hagman .

*/
#include "board/pinDefinition_Mega2560.h"
#include "Arduino.h"
#include "extLib/Pitches/pitches.h"

class Buzzer
{
private:
    
    double freq[10] = {A1,A2,A1,A3,A2,A4,A2,A3,A4};
    
public:
    Buzzer(/* args */);
    ~Buzzer();
    void outBuzz(int _tone, int _frequency);
    void sbuzz();
    void sbuzzRnd();
};

Buzzer::Buzzer(/* args */)
{
}

Buzzer::~Buzzer()
{
}

void Buzzer::outBuzz(int _frequency, int _duration)
                                                    {
                                                        tone(buzzerPin, _frequency, _duration);
                                                        delay(100);
                                                        noTone(buzzerPin);
                                                    }

void Buzzer::sbuzz()
                    {
                        for (int i = 0; i < 10; i++)
                                                        {
                                                            outBuzz(freq[i],100);
                                                        }
                        
                    }

void Buzzer::sbuzzRnd()
                    {
                        for (int i = 0; i < 5; i++)
                        {
                            int nota = random(50,1000);
                        tone(buzzerPin,nota,100);
                        delay(100);
                        }
                        
                        
                        
                        
                        
                        
                    }