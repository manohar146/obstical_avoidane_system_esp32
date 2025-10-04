/*********** BLYNK CREDENTIALS ***********/
#define BLYNK_AUTH_TOKEN "nTP7y3tPvDjYw2JG_GcIkxIL6YADGYHn"
#define BLYNK_TEMPLATE_ID "TMPL3klgoZxWl"
#define BLYNK_TEMPLATE_NAME "ondyicaleAvoidance"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*********** HARDWARE SETUP ***********/
#define IR_SENSOR_PIN 33
#define BUZZER_PIN 27
#define RED_LED 26
#define GREEN_LED 25

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust I2C address if needed

/*********** BLYNK WIFI CONFIG ***********/
char ssid[] = "Student";       // Replace with your WiFi name
char pass[] = "Learn@123";   // Replace with your WiFi password

/*********** SETUP FUNCTION ***********/
void setup() {
  Serial.begin(115200);

  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Starting System");
  delay(1500);
  lcd.clear();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

/*********** MAIN LOOP ***********/
void loop() {
  Blynk.run();

  int irValue = digitalRead(IR_SENSOR_PIN);

  if (irValue == LOW) {  // Obstacle Detected
    lcd.setCursor(0, 0);
    lcd.print("Obstacle Detected");
    lcd.setCursor(0, 1);
    lcd.print("Avoid this path ");

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    digitalWrite(BUZZER_PIN, HIGH);
    delay(300);
    digitalWrite(BUZZER_PIN, LOW);
    delay(300);

    Blynk.virtualWrite(V0, "Obstacle Detected! Avoid this path");

  } else {  // Clear Path
    lcd.setCursor(0, 0);
    lcd.print("Clear Path!     ");
    lcd.setCursor(0, 1);
    lcd.print("Proceed Safely  ");

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BUZZER_PIN, LOW);

    Blynk.virtualWrite(V0, "Clear Path! Proceed");
    delay(500);
  }
}
