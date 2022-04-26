

#include <ESP8266WiFi.h>

 
String apiKey = "apikey";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "ssidname";     // replace with your wifi ssid and wpa2 key
const char *pass =  "password";
const char* server = "api.thingspeak.com";


int TRIGGERPIN1 = D1;int ECHOPIN1 =D2;
int TRIGGERPIN2 = D3;int ECHOPIN2 =D4;



WiFiClient client;
 
void setup() 
{
       Serial.begin(9600);
       delay(10);
       pinMode(TRIGGERPIN1,OUTPUT);
       pinMode(ECHOPIN1,INPUT);
       pinMode(TRIGGERPIN2,OUTPUT);
       pinMode(ECHOPIN2,INPUT);
       pinMode(A0,INPUT);
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
long usReading1(){
  digitalWrite(TRIGGERPIN1, LOW);  
  delayMicroseconds(3); 
  
  digitalWrite(TRIGGERPIN1, HIGH);
  delayMicroseconds(12); 
  
  digitalWrite(TRIGGERPIN1, LOW);
  long duration = pulseIn(ECHOPIN1, HIGH);
  long distance = duration/(2* 29.1);
  return distance;
  }
  long usReading2(){
  digitalWrite(TRIGGERPIN2, LOW);  
  delayMicroseconds(3); 
  
  digitalWrite(TRIGGERPIN2, HIGH);
  delayMicroseconds(12); 
  
  digitalWrite(TRIGGERPIN2, LOW);
  long duration = pulseIn(ECHOPIN2, HIGH);
  long distance = duration/(2* 29.1);
  return distance;
  }
  
int entry=0;
int leaving=0;

void loop(){ 
  int neW=(analogRead,A0);
long old1,New1;
old1=usReading1();
delay(10);
New1=usReading1();

while (1){
  old1=New1;  delay(100);
  New1=usReading1();
  if (New1<old1){
    if(New1>40){
      New1=usReading1();
    }
    else{
      break;
    }
    }}

while(1){
  old1=New1;
  delay(10);
  New1=usReading1();
  if (New1<old1){
    if(New1>0 && New1<40){
      New1=usReading1();
    }
    else{
      break;
    }
    }}
    
  
    entry++;

    
long old2,New2;
old2=usReading2();
delay(10);
New2=usReading2();

while (1){
  old2=New2;  delay(100);
  New1=usReading1();
  if (New2<old2){
    if(New2>40){
      New2=usReading2();
    }
    else{
      break;
    }
    }}

while(1){
  old2=New2;
  delay(10);
  New2=usReading2();
  if (New2<old2){
    if(New2>0 && New2<40){
      New2=usReading2();
    }
    else{
      break;
    }
    }}
    leaving++;
  
 
old2=usReading2();
//delay(10);
New2=usReading2();

 while (New2<=old2){
  old2=New2;
  delay(100);
  New2=usReading2();
  if (New2>(old2+50)){
    leaving++;}
  }

Serial.print("sum is      ");
Serial.println(entry);
Serial.print("leaving is   ");
Serial.println(leaving);
Serial.print("No. of people is ");
Serial.println(entry-leaving);


delay(500);Serial.println("****************");
  
      
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(entry); 
                             postStr +="&field2=";
                             postStr += String(leaving);
                             postStr +="&field3=";
                             postStr += String(entry-leaving);
                             postStr +="&field4=";
                             postStr += String(neW);
                             postStr += "\r\r\n\r\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                                                         Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(1000);
}
