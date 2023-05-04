#include <M5StickCPlus.h>
#include <Encoder.h>

// Define the rotary encoder pins
#define ENCODER_PIN_A 25
#define ENCODER_PIN_B 0
#define BUTTON_C_PIN 26

// Define the color options
const int ARRAY_SIZE = 3;
const uint16_t colors[ARRAY_SIZE] = {RED, GREEN, BLUE};

// Define the current color index
int color_index = 0;

// Define the button state and current screen mode
bool button_c_pressed = false;

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

  // Set the initial color
  M5.Lcd.fillScreen(colors[color_index]);
}

void loop() {
  // Read the rotary encoder pins
  int a = digitalRead(ENCODER_PIN_A);
  int b = digitalRead(ENCODER_PIN_B);

  // Determine the direction of rotation
  if (a == HIGH && b == LOW) {
    if (button_c_pressed == false) {
      color_index++;
      color_index %= ARRAY_SIZE;
      M5.Lcd.fillScreen(colors[color_index]);
    }
  } else if (a == LOW && b == HIGH) {
    if (button_c_pressed == false) {
      color_index--;
      if (color_index < 0) {
        color_index = ARRAY_SIZE - 1;
      }
      M5.Lcd.fillScreen(colors[color_index]);
    }
  }

  // Read the button state and toggle the mode if pressed
  if (digitalRead(BUTTON_C_PIN) == 0) {
    button_c_pressed = !button_c_pressed;
    delay(50); // debounce delay
  } else {
    button_c_debounce = millis();
  }

  // If the button has been released for long enough, toggle the mode
  if (button_c_pressed == true && (millis() - button_c_debounce > BUTTON_C_DEBOUNCE_TIME)) {
    button_c_pressed = false;
  }
}