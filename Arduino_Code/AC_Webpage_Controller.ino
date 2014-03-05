/**
Questo codice permette di trasformare l'Arduino in un webserver, in grado di ricevere richieste dalla rete, che trasmetterà attraverso segnali ALTO all'altro
Arduino, dove sono presenti le codifiche IR da inviare al codizionatore, per accenderlo, spegnerlo
VERSIONE 1.0
AUTORE GIACOMO BELLAZZI
*/
#include <Ethernet.h>
#include <SPI.h>
#include <WebServer.h> 
#include <avr/pgmspace.h>


static byte mac_Add[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
WebServer webserver("", 80);
// Questa stringhe, permetterà di capire lo stato del condizionatore, sulla pagina web
String state = "off"; 



void Start(WebServer &server, WebServer::ConnectionType type,
           char *url_param, bool param_complete)
{
  server.httpSuccess();
  if (type != WebServer::HEAD)
  {
    String s = "";
 
     if (param_complete == true)
      {
      s = url_param;
      if ( s == "cold")
      {
        Serial.println("cold");
        state = "cold";
        sendPWMtoArduino(24);
      }
      if ( s == "warm")
      {
        Serial.println("warm");
        state = "warm";
        sendPWMtoArduino(22);
       }
     
     if ( s == "off")
      {
        Serial.println("off");
        state = "off";
        sendPWMtoArduino(26);
      }
     }
    // web page
    server.print(
    "<html><head><meta name='viewport' content='width=200px'/></head><body>"
    "<h1>A/C Arduino Remote Controller Page!</h1>");
    
    if(state=="off"){
      server.print(F("<h2>Stato AC : off </h2>"));
    }
    if(state=="cold"){
      server.print(F("<h2>Stato AC : condizionatore </h2>"));
    }
    if(state=="warm"){
      server.print(F("<h2>Stato AC : pompa di calore </h2>"));
    }
    server.println(F("<h1> </h1><BR>"));
    server.println(F("<a href='/?cold'><img src='http://ismanettoneblog.altervista.org/blog/wp-content/uploads/2014/02/cold.png'>""<a href='/?warm'><img src='http://ismanettoneblog.altervista.org/blog/wp-content/uploads/2014/02/warm.jpg'><BR>"
    "<a href='/?off'><img src='http://ismanettoneblog.altervista.org/blog/wp-content/uploads/2014/02/off.png'>"));
  }
}

 void setup()
{
  digitalWrite(22,LOW);
  digitalWrite(24,LOW);
  digitalWrite(26,LOW);
  pinMode(22,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(26,OUTPUT);
  Ethernet.begin(mac_Add);
  webserver.setDefaultCommand(&Start);
  webserver.addCommand("index.htm", &Start);
  Serial.begin(9600);
  webserver.begin();
  delay(100);
  Serial.println(Ethernet.localIP());
}
 
void loop()
{
 webserver.processConnection();
}

// Questa funzione invia il relativo segnale all'altro Arduino, che stabilirià che segnale IR dovrà inviare
void sendPWMtoArduino(int led){
  digitalWrite(led,HIGH);
  delay(1000);
  digitalWrite(led,LOW);
}





