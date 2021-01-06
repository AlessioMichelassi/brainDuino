# brainDuino
BrainDuino is a simple g-code interpreter for domestic activities.

Ex: G105 P1 S1 ; return temperature and humidity
Ex. G150 P1 S255; turn on the led number 1 at 255

To send the command currently you can use a serial monitor.

// 
L'idea è quella di creare una specie di Os per i mega 2560 in modo da utilizzarli per accendere/spengere le luci, leggere i dati dai vari sensori come umidità, temperatura, luminosità dell'ambiente
presenza di polvere, gas, co2.

Volevo sostituire le lampadine di casa con i led quando mi sono accorto che in effetti in casa, nonostante la bolletta sia alta è difficile che qualcuno abbia dei sistemi automatici per ridurre la spesa e o per ottimizzare i consumi. Le luci a led sono più economiche? I led funzionano a 12v e per funzionare ogni lampadina bisogna trasformare la corrente da 220v AC in 12v DC. Questo significa che, è più la corrente dissipata che quella utilizzata. Ad esempio in casa mia oni stanza ha un lampadario con almeno 6 lampadine da 40w. A parità di potenza/distanza con la corrente continua, in una stanza di 16/20mq si può/deve controllare con un solo traformatore. Arduino funziona bene a 12v. Ha una lunga serie di librerie e shield a basso costo disponibili anche su amazon e lo si può far comunicareanche con i nuovi sistemi tipo Alexa. A differenza del sonOff è possibile riprogrammarlo in base alle proprie esigenze e visto che 50 pin è possibile espanderlo.

Al momento funziona con 4 pulsanti a scatto della vimar, un modulo da 4 relay, un clock DS32321. Ha due termometri. Il primo è nel clock il secondo è un sensore economico di tipo DH11. ha 4 Mosfet irf520 per controllare la potenza collegati in serie alle uscite dei relay. Ogni lampadina è accesa/spenta da un relay. In questo modo posso accendere la luce in modo classico con il pulsante a parete ma anche tramite wifi o tramite seriale dal pc.

Come codice di comando ho usato il gCode. G(comando) Sensore(indirizzo) P(quantità). Quindi ad esempio G105 P1 S1 aziona la lettura del termometro che si trova all'indirizzo 1. 
