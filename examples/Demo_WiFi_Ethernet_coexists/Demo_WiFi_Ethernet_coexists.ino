/******************************************************************************************************
 * Demonstrate the coexistence of the EthernetWebServer and WiFiWebServer on ESPi Board
 * 
 * For more code examples of ESPi board: https://github.com/sbcshop/ESPi_Software/tree/main/examples
 ******************************************************************************************************/
 
#include "defines.h"

#include <WiFi.h>
#include <WebServer.h>

#include <SPI.h>
#include <EthernetWebServer.h>

#define USE_THIS_SS_PIN   5   // Ethernet CS pin connected to GPIO5 of ESP32 on ESPi board

const char* ssid     = "your ssid";  // Add your network SSID 
const char* password = "your password";  // Add your network Password

EthernetWebServer ethernetServer(80);
WebServer wifiServer(80);

const int led = 13;

void handleEthernetRoot()
{
  ethernetServer.send(200, "text/plain", "Hello from ESPi Ethernet!");
}

void handleWiFiRoot()
{
  wifiServer.send(200, "text/plain", "Hello from ESPi WiFi!");
}

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  delay(1000);

  Serial.println("*** Demo of EthernetWebServer and WiFiWebServer on ESPi Board combine ***");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Ethernet.init(USE_THIS_SS_PIN);

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  Serial.print(F("Using mac index = "));
  Serial.println(index);
  
 
  ethernetServer.on("/", handleEthernetRoot);
  ethernetServer.begin();
  Serial.print(F("HTTP EthernetWebServer is @ IP : "));
  Serial.println(Ethernet.localIP());

  wifiServer.on("/", handleWiFiRoot);
  wifiServer.begin();
  Serial.print(F("HTTP WiFiWebServer is @ IP : "));
  Serial.println(WiFi.localIP());
}

void loop()
{
  // listen for incoming clients
  ethernetServer.handleClient();

  wifiServer.handleClient();
}
