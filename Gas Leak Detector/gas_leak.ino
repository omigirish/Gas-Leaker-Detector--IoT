
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define TOKEN  "BBFF-EGEN31ho5xgqOylskN74F6m4pYFjbJ" 
char auth[] = "8sl1lR6EMRsWVw-MZtJ-2e0lqytxcy2i"; 
#define WIFISSID "Sushant"
#define PASSWORD "8291612667"
Ubidots client(TOKEN);
unsigned long lastMillis = 0;
 BlynkTimer timer;
int LDR = A0; 
int ldr_data = 0; 
int buzer= D2;
void setup(){
    Serial.begin(115200);
    pinMode(LDR, INPUT);
    digitalWrite(buzer,LOW);
    pinMode(buzer,OUTPUT); 
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
     Blynk.begin(auth, WIFISSID, PASSWORD);
     timer.setInterval(1000L, myTimerEvent);
}
void loop(){
  Blynk.run();
  timer.run();
  ldr_data = analogRead(LDR);
  if(ldr_data >500){
    Serial.println("accessing the sensor and current sensor value is greater than normal value ");
    Serial.print(ldr_data);
    Serial.print("DANGER!!!");
    digitalWrite(buzer,HIGH);
    delay(5000);
    Blynk.email("omigirish1999@gmail.com","Gas Leak Alert","A Gas leak is detected in your house.");
      Blynk.notify("Gas Leak Detected!!!!!");
      
  }
  else
  {
    Serial.println("accessing the sensor and current sensor value is ");
    Serial.print(ldr_data);
    Serial.print("every thing is NORMAL!!!");
    Blynk.virtualWrite(V4, "NO Gas leaks detected.");
  }
  client.add("GasLeakage", ldr_data);
  client.sendAll(true);
  delay(2000);
}
void myTimerEvent()
{
  Blynk.virtualWrite(V5, Data);
}
