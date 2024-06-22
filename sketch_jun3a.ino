#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin tanımları
const int gasSensorPin = A0;
const int potPin = A1;
const int joyXPin = A3;
const int joyYPin = A2;
const int joySWPin = 8;  // SW pinini dijital pine bağladık
const int buzzerPin = 9;
const int greenLEDPin = 10;
const int redLEDPin = 11;
const int bluetoothRxPin = 2;  // Bluetooth RX pini
const int bluetoothTxPin = 3;  // Bluetooth TX pini

SoftwareSerial Bluetooth(bluetoothRxPin, bluetoothTxPin);  // Bluetooth RX -> Pin 2, TX -> Pin 3

// Menü değişkenleri
int menuIndex = 0;
bool selectPressed = false;

// Eşik değeri
int threshold = 500;  // Potansiyometre ile ayarlanabilir

void setup() {
  // Seri haberleşmeyi başlat
  Serial.begin(9600);     // Seri monitör için
  Bluetooth.begin(9600);  // Bluetooth modülü için

  // LCD ekranı başlat
  lcd.begin(16, 2);
  lcd.backlight();

  // Pin modlarını ayarla
  pinMode(gasSensorPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(joyXPin, INPUT);
  pinMode(joyYPin, INPUT);
  pinMode(joySWPin, INPUT_PULLUP);  // Joystick düğmesi için pull-up direnç
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  // LCD ekranın ilk satırına bilgi yaz
  lcd.setCursor(0, 0);
  lcd.print("Ayarlar");
  lcd.setCursor(0, 1);
  lcd.print("Bildirimler");

  // Başlangıçta yeşil LED'i yak
  digitalWrite(greenLEDPin, HIGH);
  digitalWrite(redLEDPin, LOW);
}

void loop() {
  // Joystick'ten okuma yap
  int joyXValue = analogRead(joyXPin);
  int joyYValue = analogRead(joyYPin);
  int joySWState = digitalRead(joySWPin);

  // Joystick düğmesine basılma durumu
  if (joySWState == LOW && !selectPressed) {
    selectPressed = true;
    if (menuIndex == 0) {
      ayarlarMenusu();
    } else if (menuIndex == 1) {
      bildirimlerMenusu();
    }
  } else if (joySWState == HIGH) {
    selectPressed = false;
  }

  // Joystick Y ekseni hareketi (menüde gezinme)
  if (joyYValue < 400) {  // yukarı hareket
    menuIndex = 0;
  } else if (joyYValue > 600) {  // aşağı hareket
    menuIndex = 1;
  }

  // Menü ekranını güncelle
  lcd.clear();
  if (menuIndex == 0) {
    lcd.setCursor(0, 0);
    lcd.print("> Ayarlar");
    lcd.setCursor(0, 1);
    lcd.print("  Bildirimler");
  } else if (menuIndex == 1) {
    lcd.setCursor(0, 0);
    lcd.print("  Ayarlar");
    lcd.setCursor(0, 1);
    lcd.print("> Bildirimler");
  }

  // Gaz sensöründen okuma yap
  int gasValue = analogRead(gasSensorPin);
  // Gaz seviyesini Bluetooth üzerinden gönder
  Bluetooth.print("Gas Level: ");
  Bluetooth.println(gasValue);

  // Eşik değeri ile karşılaştır
  if (gasValue > threshold) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(redLEDPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(redLEDPin, LOW);
  }

  delay(200);  // Joystick'in yanlış okumalarını engellemek için bekleme süresi
}

void ayarlarMenusu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gaz Duyarliligi");
  while (true) {
    // Potansiyometreden okuma yap
    int potValue = analogRead(potPin);
    int newThreshold = map(potValue, 0, 1023, 100, 1000);

    // Eğer eşik değeri değişmişse, ekrana yaz
    if (newThreshold != threshold) {
      threshold = newThreshold;
      lcd.setCursor(0, 1);
      lcd.print("                ");  // Önceki değeri temizle
      lcd.setCursor(0, 1);
      lcd.print(threshold);
    }

    // Gaz sensöründen okuma yap ve eşik değeri ile karşılaştır
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

    // Gaz seviyesini Bluetooth üzerinden gönder
    Bluetooth.print("Gas Level: ");
    Bluetooth.println(gasValue);

    // Joystick düğmesine basılma durumu (geri dön)
    if (digitalRead(joySWPin) == LOW) {
      while (digitalRead(joySWPin) == LOW)
        ;  // Buton bırakılana kadar bekle
      lcd.clear();
      return;  // Ana menüye dön
    }
    delay(200);
  }
}

void bildirimlerMenusu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gaz Seviyesi");
  while (true) {
    // Gaz sensöründen okuma yap
    int gasValue = analogRead(gasSensorPin);

    // Gaz seviyesi değişmişse ekrana yaz
    lcd.setCursor(0, 1);
    lcd.print("                ");  // Önceki değeri temizle
    lcd.setCursor(0, 1);
    lcd.print(gasValue);

    // Gaz seviyesini Bluetooth üzerinden gönder
    Bluetooth.print("Gas Level: ");
    Bluetooth.println(gasValue);

    // Gaz sensöründen okuma yap ve eşik değeri ile karşılaştır
    if (gasValue > threshold) {
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(greenLEDPin, LOW);
      digitalWrite(redLEDPin, HIGH);
    } else {
      digitalWrite(buzzerPin, LOW);
      digitalWrite(greenLEDPin, HIGH);
      digitalWrite(redLEDPin, LOW);
    }

    // Joystick düğmesine basılma durumu (geri dön)
    if (digitalRead(joySWPin) == LOW) {
      while (digitalRead(joySWPin) == LOW)
        ;  // Buton bırakılana kadar bekle
      lcd.clear();
      return;  // Ana menüye dön
    }
    delay(200);
  }
}