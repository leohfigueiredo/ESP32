#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"'

// Initialize the OLED display using Wire library
SSD1306  display(0x3c, 5, 4);


void setup() {
 

  Serial.begin(115200);
  Serial.println();

  

    
}

void loop() {
 display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_24);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_CENTER);

  display.display();
  
  display.drawString(64, 20, "leonardo");
  delay(5000);
   display.clear();

  display.setFont(ArialMT_Plain_16);
  display.drawString(64, 20, "IoT");
  delay(1000);
  display.clear();
    // put your main code here, to run repeatedly:

}
