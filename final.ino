#include <virtuabotixRTC.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9,10);

virtuabotixRTC myRTC(5, 6, 7);
int exhaust = 2;
int button = 3;
int buzzer = 11;
int gas = A5;
int flame = 8;
int in = 12; 
int out = 4;
int sensorThres = 100;
int lastbuttonstate=LOW;
int buttonstate=LOW;


void setup() {
  myRTC.setDS1302Time(00, 59, 23, 6, 10, 1, 2019);
  pinMode(exhaust, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(gas, INPUT);
  pinMode(flame, INPUT);
  pinMode(button,OUTPUT);
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(2000);
  Serial.println("*SENSORS PROJECT*");
}

void loop() {
  myRTC.updateTime();
  int gasSensor = analogRead(gas);
  int flameSensor = digitalRead(flame);
  int buttonreading=digitalRead(button);
  
  Serial.print("Gas sensor: ");
  Serial.println(gasSensor);
  Serial.print("Flamesensor: ");
  Serial.println(flameSensor);
  
  //door lock state 
  if(buttonreading==HIGH && lastbuttonstate==LOW)
  {
    //door is closed
    buttonstate = !(buttonstate);
  }
  lastbuttonstate=buttonreading;
  Serial.println(buttonstate);
//-------------------------------------------------------------------------------------
  //intruder and burglary alert
  if(buttonstate == 1 || myRTC.hours>=22 || myRTC.hours<6)
  { 
    if(digitalRead(out)==1)
   {
     Serial.println("INTRUDER ALERT");
     Serial.println("  SOMEONE OUTSIDE  ");
     char *message="INTRUDER ALERT...!!";
     SendMessage(message);
     delay(1000);
    }
  }

  if(buttonstate == 1)
  {
    if(digitalRead(in)==1)
    {
      Serial.println("BURGLARY ALERT");
      Serial.println("BE CAREFUL");
      char *message="BURGLARY ALERT--- INFORM POLICE IF IT WASNT YOU";
      SendMessage(message);
      delay(1000);
    }
   }

   //--------------------------------------------------------------------------
  // Checks if it has reached the threshold value
  if (gasSensor > sensorThres && flameSensor == 0)
  {
    digitalWrite(exhaust, HIGH);
    tone(buzzer, 1000, 100);
    delay(100);
    tone(buzzer, 1000, 100);
    delay(100);
    tone(buzzer, 1000, 100);
    delay(100);
    tone(buzzer, 1000, 100);
    Serial.println("RED ALERT");
    Serial.println("  GET OUTSIDE  ");
    char *message="RED ALERT **GET OUTSIDE**";
    SendMessage(message);
    delay(1000);
  }
  if(gasSensor > sensorThres && flameSensor!=0)
  {
    digitalWrite(exhaust, HIGH);
    tone(buzzer, 1000, 400);

    Serial.println("LPG Gas Leakage");
    Serial.println("     Alert     ");
    char *message="**ALERT....ALERT**\nGAS LEAKAGE";
    SendMessage(message);
    delay(1000);
  }
  if(flameSensor == 0 && gasSensor<sensorThres)
  {
    digitalWrite(exhaust, HIGH);
    tone(buzzer, 1000, 400);
    Serial.println("Fire detected");
    Serial.println("     Alert     ");
    char *message="FIRE DETECTED\n\n***ALERT***";
    SendMessage(message);
    
    delay(1000);
  }
  else
  {
    digitalWrite(exhaust, LOW);
    noTone(buzzer);
    Serial.println("  No problems  ");
    Serial.println("   Safe   ");
    delay(1000);
  }
  delay(100);
}


 void SendMessage(char *k)
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919442295475\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println(k);// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
