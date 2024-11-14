// OLED libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// OLED defines
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// digital pins for distance sensor it can change for your board
#define ECHO_PIN 26
#define TRIG_PIN 25  

float distance;

void distance_calc();
void setup() {
  
  Serial.begin(9600);

  // initilaze OLED
  display.begin(i2c_Address, true);
  display.display();
  delay(2000);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  distance_calc();
  updateDisplay();
}

void distance_calc() {
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  distance = duration * 0.034 / 2;

  Serial.printf("Distance = %.2f cm \n", distance);
  delay(500);
}
void updateDisplay () {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.printf("Distance: %0.2f cm", distance);
  display.display();
  delay(2000);
  }
