#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile unsigned long pulseCount = 0;
unsigned long lastTime = 0;

float voltage = 0;
unsigned long frequency = 0;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
    pinMode(3, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(2), countPulse, RISING);

  lcd.setCursor(0,0);
  lcd.print("System Start...");
  delay(1500);
  lcd.clear();
}

void loop() {

  if (millis() - lastTime >= 1000) {

    detachInterrupt(digitalPinToInterrupt(2));
    frequency = pulseCount;
    pulseCount = 0;
    lastTime = millis();
    attachInterrupt(digitalPinToInterrupt(2), countPulse, RISING);

    // Voltage read
    int raw = analogRead(A0);
    voltage = (raw * 5.0) / 1023.0;
    voltage = voltage *56;
    

    // Condition
    bool outputState;
//
//    if ((voltage > 4.0 && frequency > 60) || 
//        (voltage < 2.0 && frequency < 50)) {
//      digitalWrite(13, LOW);
//      outputState = false;
//    } else {
//      digitalWrite(13, HIGH);
//      outputState = true;
//    }

  if (voltage < 195 || frequency < 50) {
     digitalWrite(13, LOW);
     digitalWrite(3, LOW);
     outputState = false;
  } 
  else if (voltage > 245 || frequency > 60) {
     digitalWrite(13, LOW);
     digitalWrite(3, LOW);
     outputState = false;
  } 
    else {
     digitalWrite(3, HIGH);   
     digitalWrite(13, HIGH);
     outputState = true;
  }


    

    // LCD Display
//    lcd.clear();
//
//  lcd.setCursor(0, 0);
//  lcd.print("Voltage: ");
//  lcd.print(voltage,1);
//  lcd.print(" V");
//
//  lcd.setCursor(0, 1);
//  lcd.print("Frequency: ");
//  lcd.print(frequency);
//  lcd.print(" Hz");


    if (outputState) {
    lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(voltage,1);
  lcd.print(" V");

  lcd.setCursor(0, 1);
  lcd.print("Frequency: ");
  lcd.print(frequency);
  lcd.print(" Hz");     
     delay(1500);
    
    } 
    
    
    else {
    lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("V:");
  lcd.print(voltage,1);
  lcd.print("V");

  lcd.setCursor(10, 0);
  lcd.print("F:");
  lcd.print(frequency);
  lcd.print("H");

  lcd.setCursor(0, 1);
  lcd.print(" Fault Detected "); 
    delay(1500);
    
    }
  }
}

void countPulse() {
  pulseCount++;
}