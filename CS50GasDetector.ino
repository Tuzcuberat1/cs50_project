#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin tanımları
const int gasSensorPin = A0;
const int potPin = A1;
const int joyXPin = A3;
const int joyYPin = A2;
const int joySWPin = 8;
const int buzzerPin = 9;
const int greenLEDPin = 10;
const int redLEDPin = 11;
const int bluetoothRxPin = 2;  // Bluetooth RX pin
const int bluetoothTxPin = 3;  // Bluetooth TX pin

SoftwareSerial Bluetooth(bluetoothRxPin, bluetoothTxPin);  // Bluetooth RX -> Pin 2, TX -> Pin 3

// Menu Variables
int menuIndex = 0;
bool selectPressed = false;

int threshold = 500;  // Can be changed by potentiometer

void setup() {
  // starting serial communication
  Serial.begin(9600);     // For serial monitor
  Bluetooth.begin(9600);  // For Bluetooth module

  // Starting LCD screen
  lcd.begin(16, 2);
  lcd.backlight();

  // Setting pin modes
  pinMode(gasSensorPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(joyXPin, INPUT);
  pinMode(joyYPin, INPUT);
  pinMode(joySWPin, INPUT_PULLUP);  // Pull-up resistance for joystick
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  // Creating the two different parts of menu
  lcd.setCursor(0, 0);
  lcd.print("Settings");
  lcd.setCursor(0, 1);
  lcd.print("Notifications");

  // Starting with lighting green pin
  digitalWrite(greenLEDPin, HIGH);
  digitalWrite(redLEDPin, LOW);
}

void loop() {
  // Reading from Joystick
  int joyXValue = analogRead(joyXPin);
  int joyYValue = analogRead(joyYPin);
  int joySWState = digitalRead(joySWPin);

  // ıf joystick is pressed
  if (joySWState == LOW && !selectPressed) {
    selectPressed = true;
    if (menuIndex == 0) {
      settingsMenu();
    } else if (menuIndex == 1) {
      notificationsMenu();
    }
  } else if (joySWState == HIGH) {
    selectPressed = false;
  }

  // Moving joystick in y direction
  if (joyYValue < 400) {  // Moving upwards
    menuIndex = 0;
  } else if (joyYValue > 600) {  // Moving downwards
    menuIndex = 1;
  }

  // Updating Menu screen
  lcd.clear();
  if (menuIndex == 0) {
    lcd.setCursor(0, 0);
    lcd.print("> Settings");
    lcd.setCursor(0, 1);
    lcd.print("  Notifications");
  } else if (menuIndex == 1) {
    lcd.setCursor(0, 0);
    lcd.print("  Settings");
    lcd.setCursor(0, 1);
    lcd.print("> Notifications");
  }

  // Reading from gas sensor
  int gasValue = analogRead(gasSensorPin);
  // Sending gas level via BLUETOOTH 
  Bluetooth.print("Gas Level: ");
  Bluetooth.println(gasValue);

  // Comparing normal and current values
  if (gasValue > threshold) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(redLEDPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(redLEDPin, LOW);
  }

  delay(200);  // Delay for peventing wrong readings
}

void settingsMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gaz Duyarliligi");
  while (true) {
    // Reading from potentiometer
    int potValue = analogRead(potPin);
    int newThreshold = map(potValue, 0, 1023, 100, 1000);

    // If the value is changed, write.
    if (newThreshold != threshold) {
      threshold = newThreshold;
      lcd.setCursor(0, 1);
      lcd.print("                ");  // Deleting previous value
      lcd.setCursor(0, 1);
      lcd.print(threshold);
    }

    // Reading from gas sensor
    int gasValue = analogRead(gasSensorPin);
    if (gasValue > threshold) {
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(greenLEDPin, LOW);
      digitalWrite(redLEDPin, HIGH);
    } else {
      digitalWrite(buzzerPin, LOW);
      digitalWrite(greenLEDPin, HIGH);
      digitalWrite(redLEDPin, LOW);
    }

    // Sending gas level via Bluetooth
    Bluetooth.print("Gas Level: ");
    Bluetooth.println(gasValue);

    // If clicked joystick
    if (digitalRead(joySWPin) == LOW) {
      while (digitalRead(joySWPin) == LOW)
        ;  // Waiting until the joystick is released
      lcd.clear();
      return;  // returning to the menu
    }
    delay(200);
  }
}

void notificationsMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gaz Seviyesi");
  while (true) {
    // Reading from gas sensor
    int gasValue = analogRead(gasSensorPin);

    // If gas level changes, print on screen
    lcd.setCursor(0, 1);
    lcd.print("                ");  // Delete previous value
    lcd.setCursor(0, 1);
    lcd.print(gasValue);

    // Sending gas level via Bluetooth
    Bluetooth.print("Gas Level: ");
    Bluetooth.println(gasValue);

    // Reading gas level and comparing
    if (gasValue > threshold) {
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(greenLEDPin, LOW);
      digitalWrite(redLEDPin, HIGH);
    } else {
      digitalWrite(buzzerPin, LOW);
      digitalWrite(greenLEDPin, HIGH);
      digitalWrite(redLEDPin, LOW);
    }

    // Pressing joystick
    if (digitalRead(joySWPin) == LOW) {
      while (digitalRead(joySWPin) == LOW)
        ;  // Waiting until the joystick is released
      lcd.clear();
      return;  // Returning to the main menu
    }
    delay(200);
  }
}
