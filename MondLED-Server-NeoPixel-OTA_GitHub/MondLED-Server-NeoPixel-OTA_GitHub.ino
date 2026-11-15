// This sketch runs on two boards:
//   - ESP32-C3 Super Mini (USB-C)       -> select board "ESP32C3 Dev Module"
//   - ESP8266 (Wemos D1 mini / NodeMCU) -> select your ESP8266 board
#if defined(ESP32)
  #include <WiFi.h>
  #include <ESPmDNS.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h>
#endif
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


#include <Arduino.h>
#include "LED-Server-Class.h"

// WLAN credentials are NOT stored in the repository.
// Copy "secrets.h.example" to "secrets.h" and fill in your own values.
#include "secrets.h"

// Number of LEDs in the strip
#define NUM_LEDS 15

// Pin assignment
#if defined(ESP32)
  #define LED_DATA_PIN  3         // ESP32-C3 Super Mini: GPIO3 -> 470 Ohm -> DIN of the strip
  #define INT_LED       8         // ESP32-C3 Super Mini: blue user LED on GPIO8 (active low)
#else
  #define LED_DATA_PIN  D7        // ESP8266 (Wemos D1 mini): D7 = GPIO13
  #define INT_LED       2         // ESP8266 (Wemos D1 mini): blue LED on GPIO2 (active low)
#endif

const char* ssid = SECRET_WIFI_SSID;
const char* password = SECRET_WIFI_PASSWORD;
const char* otaPassword = SECRET_OTA_PASSWORD;
const char* host = "Mond1";

LEDBandServerLibrary::LEDBandServer ledBand(LED_DATA_PIN, NUM_LEDS);

void setup() {
  Serial.begin(115200);
  Serial.println("gestartet - setup");
  ledBand.setup();
  WifiReConnect();
  OTA_setup();

}

void loop() {
  ledBand.loop();
  OTA_loop();
}


void WifiReConnect()
{
  pinMode(INT_LED, OUTPUT);         // Initialize the onboard LED pin as an output
  digitalWrite(INT_LED, HIGH);      // LED is active low -> HIGH = LED off.

  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.mode(WIFI_STA);
#if defined(ESP32)
    // Many ESP32-C3 Super Mini boards have a poorly matched antenna and fail to
    // connect with the default transmit power ("Auth Expired"). A lower power fixes this.
    // If the connection still fails, try WIFI_POWER_11dBm or WIFI_POWER_5dBm.
    WiFi.setTxPower(WIFI_POWER_8_5dBm);
#endif
    WiFi.begin(ssid, password);
    Serial.println("");
  
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    for (int i=0;i<3;i++){
      digitalWrite(INT_LED, LOW);          // turn the LED on.
      delay(500);         // wait
      digitalWrite(INT_LED, HIGH);         // turn the LED off.
      delay(500);   // wait
      delay(0);                        //to prevent watchdog firing.
    }
  }
}


void OTA_setup()
{
  ArduinoOTA.setHostname(host);
  ArduinoOTA.setPassword(otaPassword);
  ArduinoOTA.onError([](ota_error_t error) { ESP.restart(); });
  ArduinoOTA.begin();
}

void OTA_loop()
{
  ArduinoOTA.handle();
}
