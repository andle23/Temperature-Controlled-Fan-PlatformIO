#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal.h>

// Pin Definitions

#define DHTPIN 4
#define DHTTYPE DHT11

#define ENA 9 
#define IN1 2
#define IN2 5
#define BUZZER 13 
#define POT A0

// LCD pins: RS, E, D4, D5, D6, D7

LiquidCrystal lcd(6, 7, 8, 10, 11, 12);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);

  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Set motor to spin in 1 direction
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2,LOW);

  pinMode(BUZZER, OUTPUT);
  analogWrite(ENA, 0); // start motor stopped

  

}

void loop() {
  
  // Read temperature and potentiometer
  float temp = dht.readTemperature();
  int potVal = analogRead(POT);
  int tempThreshold = map(potVal, 0, 1023, 15, 30); // range


  // Display on LCD
  lcd.setCursor(0,0);
  lcd.print("                "); // clear line
  lcd.setCursor(0,0); // new line
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("C ");

  lcd.setCursor(0,1);
  lcd.print("                "); // clear line
  lcd.setCursor(0,1); // new line
  lcd.print("Thresh: ");
  lcd.print(tempThreshold);
  lcd.print("C ");


  // Determine motor speed
  int speed = 0;

  
  if(temp >= tempThreshold){

    float diff = temp - tempThreshold;

    if (diff > 10) {

      diff = 10;
    }
    if (diff < 0){

      diff = 0;
    } 

    // Map temperature difference (0–10°C) → fan speed (≈90–225, capped at 255)
    speed = 90 + (int)(diff * 13.5); 
    
    analogWrite(ENA, speed);
    

    // **Set direction pins every time fan should run**
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);


    // Passive buzzer frequency 
    int frequency = 100 + (int)((diff / 10.0) * 300);
    tone(BUZZER, frequency);

    


  }
  else{
    
     // Stop motor  
    speed = 0;
    analogWrite(ENA, speed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    noTone(BUZZER); // passive buzzer fully off


  }
  
  // Debug (uncomment to see temp/threshold/speed in Serial Monitor)
  //Serial.print("Temp: "); Serial.print(temp);
  //Serial.print(" | Thresh: "); Serial.print(tempThreshold);
  //Serial.print(" | Speed: "); Serial.println(speed);

  delay(1000);
}

