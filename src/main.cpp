#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal.h>

// Pin Definitions

#define DHTPIN 4
#define DHTTYPE DHT11

#define ENA 3
#define IN1 2
#define IN2 5
#define BUZZER 9
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

    // Scale 0–10°C above threshold to 120–255 PWM
    // speed = 120 + (int)(diff * 13.5); // 120 at threshold, 255 at +10°C
    
    speed = 255;
    analogWrite(ENA, speed);

    // **Set direction pins every time fan should run**
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

     // Passive buzzer frequency 500–1500Hz for comfort
    int frequency = 100 + (int)((diff / 10.0) * 300);
    tone(BUZZER, frequency);

    // digitalWrite(BUZZER, HIGH); this was for active buzzer


  }
  else{
    
     // Stop motor
    speed = 0;
    analogWrite(ENA, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    noTone(BUZZER); // buzzer fully off


    //speed = 0;
    //digitalWrite(BUZZER, LOW);
  }
  

  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" | Thresh: "); Serial.print(tempThreshold);
  Serial.print(" | Speed: "); Serial.println(speed);
  //analogWrite(ENA, speed);

  delay(1000);
}

