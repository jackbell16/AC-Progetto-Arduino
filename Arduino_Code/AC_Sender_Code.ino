/**
Questo programma permette di inviare dei segnali ad infrarosso al proprio condizionatore di casa, per poterlo azionare, attraverso un altro Arduino/Raspbery PI, che invia un segnale ALTO,
a seconda della configurazione impostata dall'utente, attraverso il webserver, che è presente sull'altro Arduino
VERSIONE 1.0
AUTORE GIACOMO BELLAZZI
*/
#include "IRremote.h"
#define pinWarm A0
#define pinOFF A1
#define pinCold A2 
 
IRsend irsend;
 
void setup()
{
  Serial.begin(9600);
}
// frequenza degli infrarossi per l'AC
int khz=38; 
// ON and 2O C° with 1 FAN heat
unsigned heat[] = {3000,3000,3000,4400,550,1600,600,550,550,1650,550,550,550,550,550,1650,550,550,550,1650,500,550,550,1650,550,550,550,500,600,500,600,550,550,550,550,1650,500,550,550,600,500,1700,500,550,550,550,550,550,550,600,500,550,550,550,550,550,550,550,550,1650,550,1650,550,1650,500,1650,550,1650,550,550,550,550,550,550,550,550,550,1650,550,1650,550,500,550,550,550,1700,500,1650,550,550,550,500,600,550,550,550,550,550,550,550,550,550,550,1650,500,1700,500,550,550,550,550,550,550,550,550,550,550,600,500,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,500,550,1700,500,550,550,550,550,550,550,1650,550};
// OFF the A/C
unsigned OFF[] = {3100,2900,2950,4400,700,1500,700,400,700,1500,700,400,650,450,550,1650,550,550,650,1500,600,500,600,1600,600,500,600,500,600,450,650,450,600,550,550,550,550,550,550,600,500,1600,600,500,600,500,600,550,550,500,600,500,600,550,550,550,550,1600,600,500,600,500,600,500,550,1650,550,1600,600,500,600,500,600,550,550,550,550,1600,600,1600,550,550,550,550,550,1650,550,1600,600,550,550,500,600,500,600,550,550,550,550,500,600,500,600,1600,600,1600,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,500,600,550,550,550,550,500,600,500,600,500,600,1600,600,500,600,1600,550,550,550,1600,600,550,550,550,550};
// ON and 23° with 2 FAN cold 
unsigned cold[] = {3050,3000,3000,4400,550,1600,600,550,550,1650,550,550,550,550,550,1650,550,500,600,1600,550,550,550,1650,550,1650,550,1650,550,550,550,550,550,500,600,1600,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,550,500,600,1650,500,550,550,600,500,1700,500,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,1650,550,550,550,500,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,550,550,550,550,550,550,550,550,500,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,550,1600,600,550,550};

void loop() {

// Invio il segnale di accenedre il condizionatore sul CALDO 
if(verificaRicezioneSegnaleALTO(pinWarm)){
  irsend.sendRaw(heat, sizeof(heat)/sizeof(int),khz); 
  delay(1000);
}
// Invio il segnale di accedere il condizionatore sul FREDDO
if(verificaRicezioneSegnaleALTO(pinOFF)){
  irsend.sendRaw(OFF, sizeof(OFF)/sizeof(int),khz); 
  delay(1000);
}
// Invio il segnale di spegnere il dispositivo
if(verificaRicezioneSegnaleALTO(pinCold)){
  irsend.sendRaw(cold, sizeof(cold)/sizeof(int),khz); 
  delay(1000);
  }
}

// Questa funziona stabilisce se a quella porta, è stata inviato un segnale dall'altro Arduino
boolean verificaRicezioneSegnaleALTO (int porta){
  if(analogRead(porta)>1000){
    return true;
  }else{
    return false;
  }
}  
