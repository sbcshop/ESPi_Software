/******************************************************************************************************
 * Application Demo code to connect ThingSpeak cloud server and send Data 
 * Here Ethernet facility of ESPi board is used for internet connection
 * Create account on thingspeak using https://thingspeak.com/ and get API key needed for this example
 * 
 * For more code examples of ESPi board: https://github.com/sbcshop/ESPi_Software/tree/main/examples
 ******************************************************************************************************/

#include <Adafruit_GFX.h>    // graphics library
#include <Adafruit_ST7789.h> // ST7789 display driver library
#include <SPI.h>             
#include "defines.h"

char server[] = "api.thingspeak.com"; // for thingspeak cloud server 

// Initialize the Ethernet client object
EthernetClient client;
#define ET_CS   5   // Ethernet 5100 chip CS pin connected GPIO5 of ESP


// Define and configure SPI pins for ESP32 and Display interfacing
#define TFT_CS        15  // chip select pin
#define TFT_RST       26  // Reset pin
#define TFT_DC        27  // Data/Command pin of SPI interface
#define TFT_MOSI      13  // DIN -> MOSI (Master OUT Slave IN) pin of SPI interface
#define TFT_SCLK      14  // SCK -> Clock pin of SPI interface for Display
#define BackLight     4   // Backlight pin of Display

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

String apiKey = "STWV4C6LDNGIXUKH";   // add your API key of Thingspeak
String dataVal = "field1=40"; // define data field created with value to upload on cloud

void setup()
{
  Serial.begin(115200);   // Set serial communication with suitable baudrate
  pinMode(BackLight, OUTPUT); // configure backlight pin as OUTPUT
  digitalWrite(BackLight,HIGH); // activate backlight 
  
  while (!Serial && millis() < 5000);
  
  tft.init(135, 240);           // Initialize display 
  tft.fillScreen(ST77XX_BLACK);
  
  Serial.print("\nStarting WebClient... "); 

  tft.setRotation(3);
  tft.setTextSize(4);
  displayText("ESPi", ST77XX_CYAN,70,20);
  tft.setTextSize(2);
  displayText("SB Components", ST77XX_BLUE,45,90);
  delay(1000);

  tft.setTextSize(3);
  tft.fillScreen(ST77XX_BLACK);
  displayText("Hello...!", ST77XX_CYAN,60,40);

  ETG_LOGWARN1(F("ESP32 setCsPin:"), ET_CS);
  Ethernet.init(ET_CS);
 
  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  Serial.println("=========================");
  Serial.println("Currently Used SPI pinout:");
  Serial.print("MOSI:");
  Serial.println(PIN_MOSI);
  Serial.print("MISO:");
  Serial.println(PIN_MISO);
  Serial.print("SCK:");
  Serial.println(PIN_SCK);
  Serial.print("SS:");
  Serial.println(ET_CS);
  Serial.println(F("========================="));

  Serial.print(F("Using mac index = "));
  Serial.println(index);

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());

  String ipAddr = String() + Ethernet.localIP()[0] + "." + Ethernet.localIP()[1] + "." + Ethernet.localIP()[2] + "." + Ethernet.localIP()[3];
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  displayText("IP Add:", ST77XX_YELLOW,10,10);
  displayText(ipAddr, ST77XX_YELLOW,10,40);
  delay(1000);

  if (Ethernet.getAltChip() == w5100s)
  {
    Serial.print(F("Speed: "));    Serial.print(Ethernet.speedReport());
    Serial.print(F(", Duplex: ")); Serial.print(Ethernet.duplexReport());
    Serial.print(F(", Link status: ")); Serial.println(Ethernet.linkReport());
  }

  Serial.println();
  Serial.println(F("Starting connection to server..."));
}

void loop()
{
  printoutData();
  // if you get a connection, report back via serial
  if (client.connect(server, 80))
  {
      Serial.println(F("Connected to server"));
      Serial.println("Sending data to ThingSpeak...");
      
      tft.fillScreen(ST77XX_BLACK);
      tft.setTextSize(2);
      displayText("Server Connected!", ST77XX_YELLOW,10,10);
      displayText("Sending...", ST77XX_YELLOW,10,40);
      
      client.print(F("POST /update HTTP/1.1\r\n"));
      client.print(F("Host: api.thingspeak.com\r\n"));
      client.print(F("Connection: close\r\n"));
      client.print(F("X-THINGSPEAKAPIKEY: "));
      
      client.print(apiKey);
      
      client.print(F("\r\n"));
      client.print(F("Content-Type: application/x-www-form-urlencoded\r\n"));
      client.print(F("Content-Length: "));
      client.print(dataVal.length());
      client.print(F("\r\n\r\n"));
      client.print(dataVal);              // sending data on cloud
      
      int statusCode = client.parseInt();
      Serial.print("HTTP status code: ");
      Serial.println(statusCode);
      client.stop();
      tft.fillScreen(ST77XX_BLACK);
      tft.setTextSize(3);
      displayText("Done!", ST77XX_YELLOW,30,30);
    }
    
  delay(5000); // wait for 5 seconds
}

void printoutData()
{
  // if there are incoming bytes available
  // from the server, read them and print them
  while (client.available())
  {
    char c = client.read();
    Serial.write(c);
    Serial.flush();
  }
}

void displayText(String text, uint16_t color, int x, int y) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
