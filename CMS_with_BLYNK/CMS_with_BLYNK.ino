#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "token";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ssid";
char pass[] = "password";



int TRIGGERPIN1 = D1;int ECHOPIN1 =D2;
int TRIGGERPIN2 = D3;int ECHOPIN2 =D4;


void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(TRIGGERPIN1,OUTPUT);
  pinMode(ECHOPIN1,INPUT);
   pinMode(TRIGGERPIN2,OUTPUT);
  pinMode(ECHOPIN2,INPUT);
  // put your setup code here, to run once:

}
int entry=0;
int leaving=0;
void loop() {
  
  
long old1,New1;
old1=usReading1();
delay(10);
New1=usReading1();

while (New1<=old1){
  old1=New1;  delay(100);
  New1=usReading1();
  if (New1>(old1+50)){
    entry++;}
  }
long old2,New2;
old2=usReading2();
delay(10);
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
Blynk.virtualWrite(V5,entry);
Blynk.virtualWrite(V6,leaving);
Blynk.virtualWrite(V7,(entry-leaving));
Blynk.run();
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
