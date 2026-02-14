#include <LiquidCrystal.h>

// ---- Pins SAME as previous circuit ----
const int trigPin = 7;
const int echoPin = 6;

const int ledA = 9;
const int ledB = 10;
const int ledC = A0;
const int ledD = A1;

const int buzzerPin = 8;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
  pinMode(ledD, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Distance:");
}

void loop() {
  long duration, cm;

  // Ultrasonic trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  cm = duration * 0.034 / 2;

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("Distance: ");
  lcd.print(cm);
  lcd.print(" cm");

  // ---- 50 cm Zone Division ----
  if (cm > 40 && cm <= 50) {
    allOff();
    lcd.setCursor(0, 0);
    lcd.print("Safe Level      ");
    digitalWrite(buzzerPin, LOW);

  } else if (cm > 30 && cm <= 40) {
    ledOn(ledA);
    lcd.setCursor(0, 0);
    lcd.print("Normal Level    ");
    digitalWrite(buzzerPin, LOW);

  } else if (cm > 20 && cm <= 30) {
    ledOn(ledB);
    lcd.setCursor(0, 0);
    lcd.print("Above Normal    ");
    digitalWrite(buzzerPin, LOW);

  } else if (cm > 10 && cm <= 20) {
    ledOn(ledC);
    lcd.setCursor(0, 0);
    lcd.print("Warning Level   ");
    digitalWrite(buzzerPin, LOW);

  } else if (cm >= 0 && cm <= 10) {
    ledOn(ledD);
    lcd.setCursor(0, 0);
    lcd.print("Red Alert!!!    ");
    digitalWrite(buzzerPin, HIGH);

  } else {
    allOff();
    lcd.setCursor(0, 0);
    lcd.print("Out of Range    ");
    digitalWrite(buzzerPin, LOW);
  }

  delay(200);
}

// ---- Helper Functions ----
void allOff() {
  digitalWrite(ledA, LOW);
  digitalWrite(ledB, LOW);
  digitalWrite(ledC, LOW);
  digitalWrite(ledD, LOW);
}

void ledOn(int ledPin) {
  allOff();
  digitalWrite(ledPin, HIGH);
}
