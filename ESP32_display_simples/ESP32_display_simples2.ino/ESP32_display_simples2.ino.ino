
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"'
#include <WiFi.h>

// Initialize the OLED display using Wire library
SSD1306  display(0x3c, 5, 4);


char *ssid      = "LudwigEFigueiredo";               // Set you WiFi SSID
char *password  = "41992549713";               // Set you WiFi password




void setup() {
  display.init();
  display.flipScreenVertically();
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_24);
  Serial.begin(115200);
  Serial.println();
  //********************
  display.display();
  display.clear();
  display.drawString(64, 20, String("Booted"));
  delay(2000);
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(64, 20, String("Connecting to Wi-Fi"));
  delay(2000);
 
  display.display();
  Serial.println("Booted");
  Serial.println("Connecting to Wi-Fi");

  WiFi.mode(WIFI_STA);
  WiFi.begin (ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
}

void loop() {

 
display.clear();

display.setFont(ArialMT_Plain_24);

  display.drawString(64, 20, "Leonardo");
  delay(5000);
  display.drawLine(   0, 12, 127, 12); //linha superior
  display.drawLine(   0, 63, 127, 63); //linha inferior

 
  display.display();
  display.clear();

  delay(5000);
  display.setFont(ArialMT_Plain_24);
  display.drawString(64, 20, "IoT");
  display.drawLine(   0, 12,   0, 63); //linha lateral esquerda
  display.drawLine( 127, 12, 127, 63); //linha lateral direita
 
  display.display();

  delay(10);

    
  }

