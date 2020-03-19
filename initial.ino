o
#include <virtuabotixRTC.h>

#include <MyRealTimeClock.h>

#include <LiquidCrystal.h>


LiquidCrystal lcd(3, 2, 4, 5, 6, 7);
virtuabotixRTC myRTC(5, 6, 7);
int exhaust = 1;
int buzzer = 9;
int gas = A5;
int flame = 8
int define echoPin1 = 12 // Echo Pin
int trigPin1 = 13 // Trigger Pin
int define echoPin1 = 10 // Echo Pin
int trigPin1 = 11 // Trigger Pin
// Your threshold value
int sensorThres = 400;
long duration, distance,m1,m2,d1,d2;


  
void setup() {
  myRTC.setDS1302Time(00, 59, 23, 6, 10, 1, 2014);
  pinMode(exhaust, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(gas, INPUT);
  pinMode(flame, INPUT);
  Serial.begin(9600);
  delay(2000);
  lcd.begin(16, 2);
  lcd.print("sensors project");
  m1=ultrasonic(trigpin1,echopin1);
  delay(2000);
  m2=ultrasonic(trigpin2,echopin2);
  delay(2000);
}

void loop() {
  myRTC.updateTime(); 
  int gasSensor = analogRead(gas);
  int flameSensor = digitalRead(flame);
  
  d1=ultrasonic(trigpin1,echopin1);
  if(button == 1 || myRTC.hours>22)
  { 
    if(d1<=(m1*3)/4)
   {
     lcd.clear();
     lcd.print("INTRUDER ALERT");
      lcd.setCursor(0, 1);
      lcd.print("  SOMEONE OUTSIDE  ");
    }
  }
  d2=ultrasonic(trigpin2,echopin2);
  if(button==1)
  {
    if(d2<=(m2*3)/4)
    {
      lcd.clear();
      lcd.print("ENTERED WITHOUT");
      lcd.setCursor(0, 1);
      lcd.print("PERMISSION");
    }
  Serial.print("Pin A5: ");
  Serial.println(gasSensor);
  Serial.print("Pin D8: ");
  Serial.println(flameSensor);
  // Checks if it has reached the threshold value
  if (gasSensor > sensorThres && flameSensor == 0)
  {
    digitalWrite(exhaust, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 400);
    lcd.clear();
    lcd.print("RED ALERT");
    lcd.setCursor(0, 1);
    lcd.print("  GET OUTSIDE  ");
    delay(500);
  }
  else if (gasSensor > sensorThres)
  {
    digitalWrite(exhaust, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 400);
    lcd.clear();
    lcd.print("LPG Gas Leakage");
    lcd.setCursor(0, 1);
    lcd.print("     Alert     ");
    delay(500);
  }
  else if(flameSensor == 0)
  {
    digitalWrite(exhaust, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 400);
    lcd.clear();
    lcd.print("Fire detected");
    lcd.setCursor(0, 1);
    lcd.print("     Alert     ");
    delay(500);
  }
  else
  {
    digitalWrite(exhaust, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
    lcd.clear();
    lcd.print("  No problems  ");
    lcd.setCursor(0,1);
    lcd.print("   Safe   ");
    delay(1000);
  }
  delay(100);
}

long ultrasonic(int x,int y)
{
  digitalWrite(x, LOW); 
 delayMicroseconds(2); 

 digitalWrite(x, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(x, LOW);
 duration = pulseIn(y, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
  // distance = microsecondsToCentimeters(duration);
 return distance;
}
