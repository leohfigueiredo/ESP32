/*
    Video: https://www.youtube.com/watch?v=oCMOYS71NIU
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini

   Create a BLE server that, once we receive a connection, will send periodic notifications.
   The service advertises itself as: 6E400001-B5A3-F393-E0A9-E50E24DCCA9E
   Has a characteristic of: 6E400002-B5A3-F393-E0A9-E50E24DCCA9E - used for receiving data with "WRITE" 
   Has a characteristic of: 6E400003-B5A3-F393-E0A9-E50E24DCCA9E - used to send data with  "NOTIFY"

   The design of creating the BLE server is:
   1. Create a BLE Server
   2. Create a BLE Service
   3. Create a BLE Characteristic on the Service
   4. Create a BLE Descriptor on the characteristic
   5. Start the service.
   6. Start advertising.

   In this example rxValue is the data received (only accessible inside that function).
   And txValue is the data to be sent, in this example just a byte incremented every second. 
*/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include "SSD1306.h"
SSD1306  display(0x3c, 5, 4);

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
float txValue = 0;
const int readPin = 25; // Use GPIO number. See ESP32 board pinouts
const int LED = 13; // Could be different depending on the dev board. I used the DOIT ESP32 dev board.

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
  display.init();
      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");

        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }

        Serial.println();
        Serial.println("*********");
      }

      // Do stuff based on the command received from the app
      // For some reason using rxValue.compare("A") == 0 doesn't work. Maybe
      // there are hidden characters I'm not seeing?
      if (rxValue.find("A") != -1) { 
        Serial.println("Turning ON!");
        digitalWrite(LED, HIGH);
        display.flipScreenVertically();
  display.drawString(64, 20, "LIGADO");

  display.display();
   
      }
      else if (rxValue.find("B") != -1) {
        Serial.println("Turning OFF!");
        digitalWrite(LED, LOW);
        display.flipScreenVertically();
  display.drawString(64, 20, "DESLIGADO");

  display.display();
      }
    }
};

void setup() {
  Serial.begin(115200);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_24);
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.display();



  pinMode(LED, OUTPUT);

  // Create the BLE Device
  BLEDevice::init("ESP32 UART Test"); // Give it a name

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TX,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
                      
  pCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_RX,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");


    display.drawLine(   0, 12, 127, 12); //linha superior
  display.drawLine(   0, 63, 127, 63); //linha inferior

 
  display.display();
  display.clear();

  delay(3000);
  display.setFont(ArialMT_Plain_24);
  display.drawString(64, 10, "Conectando");
  display.drawLine(   0, 12,   0, 63); //linha lateral esquerda
  display.drawLine( 127, 12, 127, 63); //linha lateral direita

  display.display();
  display.clear();
  delay(1000);

  display.setFont(ArialMT_Plain_24);
  display.drawString(64, 20, "Conectando");
  display.drawLine(   0, 12,   0, 63); //linha lateral esquerda
  display.drawLine( 127, 12, 127, 63); //linha lateral direita

  display.display();
  display.clear();

  delay(1000);
  display.setFont(ArialMT_Plain_24);
  display.drawString(64, 30, "Conectando");
  display.drawLine(   0, 12,   0, 63); //linha lateral esquerda
  display.drawLine( 127, 12, 127, 63); //linha lateral direita
  

  display.display();
  display.clear();

  delay(1000);
  display.setFont(ArialMT_Plain_24);
  display.drawString(64, 40, "IoT");
  display.drawLine(   0, 12,   0, 63); //linha lateral esquerda
  display.drawLine( 127, 12, 127, 63); //linha lateral direita
 
  display.display();

  display.clear();
}

void loop() {
  if (deviceConnected) {
    // Fabricate some arbitrary junk for now...
    txValue = analogRead(readPin) / 3.456; // This could be an actual sensor reading!

    // Let's convert the value to a char array:
    char txString[8]; // make sure this is big enuffz
    dtostrf(txValue, 1, 2, txString); // float_val, min_width, digits_after_decimal, char_buffer
    
//    pCharacteristic->setValue(&txValue, 1); // To send the integer value
//    pCharacteristic->setValue("Hello!"); // Sending a test message
    pCharacteristic->setValue(txString);
    
    pCharacteristic->notify(); // Send the value to the app!
    Serial.print("*** Sent Value: ");
    Serial.print(txString);
    Serial.println(" ***");

      display.setFont(ArialMT_Plain_24);
  display.drawString(64, 20, "Conectado!");
  display.drawLine(   0, 12,   0, 63); //linha lateral esquerda
  display.drawLine( 127, 12, 127, 63); //linha lateral direita
  display.drawLine(   0, 12, 127, 12); //linha superior
  display.drawLine(   0, 63, 127, 63); //linha inferior
  delay(1000);

  display.display();
  display.clear();
  display.setFont(ArialMT_Plain_24);
  display.drawString(64, 10, "Pressione");
  delay(1000);
  display.setFont(ArialMT_Plain_24);
  display.drawString(64, 30, "botão");
  delay(1000);

    
  }
  delay(1000);
    display.display();
  display.clear();
}
