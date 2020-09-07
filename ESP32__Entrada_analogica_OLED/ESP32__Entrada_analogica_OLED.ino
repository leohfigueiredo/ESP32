
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"'

int sensorPin = 2;   // select the input pin for ldr
int sensorValue = 0;  // variable to store the value coming from the sensor

// Initialize the OLED display using Wire library
SSD1306  display(0x3c, 5, 4);

void setup() {
  pinMode(sensorPin, INPUT);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_24);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  delay(1000);
  display.clear();
  Serial.print(sensorValue);

  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(sensorValue));
  display.setFont(ArialMT_Plain_24);

  display.display();

  delay(10);
}

