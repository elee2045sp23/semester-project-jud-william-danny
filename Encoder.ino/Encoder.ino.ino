#include <M5StickCPlus.h>

#define ENC_A_PIN 25
#define ENC_B_PIN 0
#define BUTTON_PIN 26

volatile int encPos = 0;
volatile bool isCW = false;
volatile bool isCCW = false;
volatile unsigned long lastInterruptTime = 0;
volatile bool isButtonPressed = false;
volatile bool isButtonLongPressed = false;
unsigned long buttonPressStartTime = 0;

void IRAM_ATTR buttonInterrupt() {
  unsigned long buttonPressDuration = millis() - buttonPressStartTime;
  if (buttonPressDuration < 500) { // short button press
    isButtonPressed = true;
  } else { // long button press
    isButtonLongPressed = true;
  }
}

void encoderInterrupt() {
  int aVal = digitalRead(ENC_A_PIN);
  int bVal = digitalRead(ENC_B_PIN);
  if (aVal == bVal) {
    encPos--;
    isCCW = true;
  } else {
    encPos++;
    isCW = true;
  }
  lastInterruptTime = millis();
}

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("Encoder Test");
  pinMode(ENC_A_PIN, INPUT_PULLUP);
  pinMode(ENC_B_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENC_A_PIN), encoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B_PIN), encoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonInterrupt, FALLING);
}

void loop() {
  M5.update();
  if (isButtonPressed) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("Short Press");
    isButtonPressed = false;
  }
  if (isButtonLongPressed) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("Long Press");
    isButtonLongPressed = false;
  }
  if (isCW) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print("CW: ");
    M5.Lcd.println(encPos);
    isCW = false;
  }
  if (isCCW) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print("CCW: ");
    M5.Lcd.println(encPos);
    isCCW = false;
  }
  if (digitalRead(BUTTON_PIN) == LOW) {
    buttonPressStartTime = millis();
  }
}
