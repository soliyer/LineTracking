#define PIN_DIRECTION_RIGHT 3
#define PIN_DIRECTION_LEFT  4
#define PIN_MOTOR_PWM_RIGHT 5
#define PIN_MOTOR_PWM_LEFT  6
#include "Freenove_WS2812B_RGBLED_Controller.h"

#define I2C_ADDRESS  0x20
#define LEDS_COUNT   10

Freenove_WS2812B_Controller strip(I2C_ADDRESS, LEDS_COUNT, TYPE_GRB);

u8 m_color[5][3] = {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}};



void setup() {
  pinMode(PIN_DIRECTION_LEFT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_LEFT, OUTPUT);
  pinMode(PIN_DIRECTION_RIGHT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_RIGHT, OUTPUT);
}

#define THRESHOLD 500 // Example threshold value for line detection

void loop() {
  int leftSensorValue = analogRead(A1);
  int middleSensorValue = analogRead(A2);
  int rightSensorValue = analogRead(A3);
  lightUpLeds();
  
  if (middleSensorValue < THRESHOLD) {
    // Line is under the middle sensor
    moveForward();
  } else if (leftSensorValue < THRESHOLD) {
    // Line is under the left sensor
    turnLeft();
   
  } else if (rightSensorValue < THRESHOLD) {
    // Line is under the right sensor
    turnRight();
   
  } else {
    // No line is detected
    stopMotors();
  }
  
  delay(20); // Short delay to prevent jitter
}


void lightUpLeds() {
  // Define the colors
  int red = 255, green = 255, blue = 255; // Start with white

  for (int i = 0; i < LEDS_COUNT; i++) {
    // Cycle through the colors for each LED
    switch (i % 4) { // Modulus operator to cycle through 0-3
      case 0: // Green
        red = 0; green = 255; blue = 0;
        break;
      case 1: // Red
        red = 255; green = 0; blue = 0;
        break;
      case 2: // Blue
        red = 0; green = 0; blue = 255;
        break;
      case 3: // White
        red = 255; green = 255; blue = 255;
        break;
    }
    strip.setLedColor(i, red, green, blue); // Set color for each LED
  }
  strip.show(); // Apply the colors to the LEDs
}

void moveForward() {
  digitalWrite(PIN_DIRECTION_LEFT, HIGH);
  digitalWrite(PIN_DIRECTION_RIGHT, LOW);
  analogWrite(PIN_MOTOR_PWM_LEFT, 130);
  analogWrite(PIN_MOTOR_PWM_RIGHT, 130);
  delay(50);
  stopMotors();
}

void moveBackward() {
  digitalWrite(PIN_DIRECTION_LEFT, LOW);
  digitalWrite(PIN_DIRECTION_RIGHT, HIGH);
  analogWrite(PIN_MOTOR_PWM_LEFT, 180);
  analogWrite(PIN_MOTOR_PWM_RIGHT, 180);
  delay(50);
  stopMotors();
}

void turnRight() {
  digitalWrite(PIN_DIRECTION_RIGHT, HIGH);
  analogWrite(PIN_MOTOR_PWM_RIGHT, 180);
  delay(50);
  stopMotors();
}

void turnLeft() {
  
  digitalWrite(PIN_DIRECTION_LEFT, LOW);
  analogWrite(PIN_MOTOR_PWM_LEFT, 180);

  delay(50);
  stopMotors();
}

void stopMotors() {
  analogWrite(PIN_MOTOR_PWM_LEFT, 0);
  analogWrite(PIN_MOTOR_PWM_RIGHT, 0);
}
