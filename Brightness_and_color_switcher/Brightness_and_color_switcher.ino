#include <M5StickCPlus.h>

// Define the rotary encoder pins
#define ENCODER_PIN_A 26
#define ENCODER_PIN_B 0
#define BUTTON_C_PIN 25

// Define the color options
const int ARRAY_SIZE = 3;
const char *colors[ARRAY_SIZE] = {"Red", "Green", "Blue"};

// Define the current color and brightness levels
int color = 0;
int brightness = 50;

// Define the button state and current screen mode
bool button_c_pressed = false;
bool brightness_screen_mode = false;

const int BUTTON_C_DEBOUNCE_TIME = 50; // in milliseconds
unsigned long button_c_debounce = 0;

void setup() {
  // Initialize the M5StickC display
  M5.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.setRotation(3); // Rotate display to landscape mode

  // Initialize the rotary encoder pins as inputs
  pinMode(ENCODER_PIN_A, INPUT);
  pinMode(ENCODER_PIN_B, INPUT);

  // Initialize the C button pin as input
  pinMode(BUTTON_C_PIN, INPUT_PULLUP); // Enable internal pull-up resistor

  // Set the initial color and brightness levels
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Color: %s", colors[color]);
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
      if (brightness_screen_mode == false) {
        M5.Lcd.printf("Color: %s", colors[color]);
      } else {
        brightness = constrain(brightness + 10, 0, 255);
        M5.Lcd.printf("Brightness: %d", brightness);
      }
    } else {
      if (brightness_screen_mode == true) {
        brightness = constrain(brightness + 10, 0, 255);
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.printf("Brightness: %d", brightness);
      }
    }
  } else if (a == LOW && b == HIGH) {
    if (button_c_pressed == false) {
      color--;
      if (color < 0) {
        color = ARRAY_SIZE - 1;
      }
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0);
      if (brightness_screen_mode == false) {
        M5.Lcd.printf("Color: %s", colors[color]);
      } else {
        brightness = constrain(brightness - 10, 0, 255);
        M5.Lcd.printf("Brightness: %d", brightness);
      }
    } else {
      if (brightness_screen_mode == true) {
        brightness = constrain(brightness - 10, 0, 255);
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.printf("Brightness: %d", brightness);
      }
    }
  }

  // Read the button state and toggle the mode if pressed
  if (digitalRead(BUTTON_C_PIN) == 0) {
    button_c_pressed = !button_c_pressed;
    delay(50); // debounce delay
    if (button_c_pressed == true) {
      // Switch to the brightness screen
      brightness_screen_mode = true;
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.printf("Brightness: %d", brightness);
    } else {
      // Switch back to the color screen
      brightness_screen_mode = false;
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.printf("Color: %s", colors[color]);
    }
  }
}

