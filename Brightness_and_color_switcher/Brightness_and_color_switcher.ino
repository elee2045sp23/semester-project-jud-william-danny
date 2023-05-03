#include <M5StickCPlus.h>

// Define the rotary encoder pins
#define ENCODER_PIN_A 26
#define ENCODER_PIN_B 36
#define BUTTON_C_PIN 37

// Define the color options
const int ARRAY_SIZE = 3;
const char *colors[ARRAY_SIZE] = {"Red", "Green", "Blue"};

// Define the current color and brightness levels
int color = 0;
int brightness = 50;

// Define the button state
bool button_c_pressed = false;

void setup() {
  // Initialize the M5StickC display
  M5.begin();

  // Initialize the rotary encoder pins as inputs
  pinMode(ENCODER_PIN_A, INPUT);
  pinMode(ENCODER_PIN_B, INPUT);

  // Initialize the C button pin as input
  pinMode(BUTTON_C_PIN, INPUT);

  // Set the initial color and brightness levels
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Color: %s\nBrightness: %d", colors[color], brightness);
}

void loop() {
  // Read the rotary encoder pins
  int a = digitalRead(ENCODER_PIN_A);
  int b = digitalRead(ENCODER_PIN_B);

  // Determine the direction of rotation
  if (a == HIGH && b == LOW) {
    if (button_c_pressed == false) {
      color++;
      color %= ARRAY_SIZE;
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.printf("Color: %s\nBrightness: %d", colors[color], brightness);
    } else {
      brightness++;
      brightness = constrain(brightness, 0, 255);
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.printf("Color: %s\nBrightness: %d", colors[color], brightness);
    }
  } else if (a == LOW && b == HIGH) {
    if (button_c_pressed == false) {
      color--;
      if (color < 0) {
        color = ARRAY_SIZE - 1;
      }
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.printf("Color: %s\nBrightness: %d", colors[color], brightness);
    } else {
      brightness--;
      brightness = constrain(brightness, 0, 255);
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.printf("Color: %s\nBrightness: %d", colors[color], brightness);
    }
  }

  // Read the button state and toggle the mode if pressed
  if (digitalRead(BUTTON_C_PIN) == 0) {
    button_c_pressed = !button_c_pressed;
    delay(50); // debounce delay
  }

  // Delay to prevent flicker
  delay(10);
}
