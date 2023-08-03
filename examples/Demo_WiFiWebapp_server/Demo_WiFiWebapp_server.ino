/******************************************************************************************************
 * Demo WiFiWebServer Application on ESPi Board
 * 
 * For more code examples of ESPi board: https://github.com/sbcshop/ESPi_Software/tree/main/examples
 ******************************************************************************************************/

#include <WiFi.h> // Add WiFi library 
#include <Adafruit_GFX.h>    // graphics library
#include <Adafruit_ST7789.h> // ST7789 display driver library
#include <SPI.h>    


// Replace with your network credentials
const char* ssid = "YourSSID";         //Add Your Network SSID
const char* password = "Yourpassword"; // Add Your Network Password

// Set web server port number to 80
WiFiServer server(80);

// Define and configure SPI pins for ESP32 and Display interfacing
#define TFT_CS        15  // chip select pin
#define TFT_RST       26  // Reset pin
#define TFT_DC        27  // Data/Command pin of SPI interface
#define TFT_MOSI      13  // DIN -> MOSI (Master OUT Slave IN) pin of SPI interface
#define TFT_SCLK      14  // SCK -> Clock pin of SPI interface for Display

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String displayState = "off";

const int BackLight = 4;    // Backlight pin of Display

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(BackLight, OUTPUT);
  tft.init(135, 240);           // Initialize display 
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("Display is Switching on!");
              displayState = "on";
              displayON(); // call function to switch on display to show some text on it
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("Display is Switching off!");
              displayState = "off";
              displayOFF(); // function will switch off display
            } 
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off button
            client.println("<style>html { font-family: Helvetica; display: flex; align-items: center; justify-content: center; height: 100%;}");
            // Set button style like add padding, make corners rounded, increase button size
            client.println(".button { border: none; color: white; padding: 24px 60px; border-radius: 12px; font-size: 36px; text-decoration: none; margin: 2px; cursor: pointer;}");
            // Set style for the ON button
            client.println(".button-on { background-color: #007BFF; }");
            // Set style for the OFF button
            client.println(".button-off { background-color: #555555; }</style></head>");
            
            // Web Page Heading
            client.println("<body><h1 style=\"text-align: center;\">ESPi WiFi Webserver</h1>");
            
            // Display ON/OFF 
            if (displayState == "off") {
              client.println("<p style=\"text-align: center;\"><a href=\"/4/on\"><button class=\"button button-on\">ON</button></a></p>");
            } else {
              client.println("<p style=\"text-align: center;\"><a href=\"/4/off\"><button class=\"button button-off\">OFF</button></a></p>");
            }
            
            // Display current state of Display as message below the button
            client.println("<p style=\"text-align: center;\">Display is " + displayState + "</p>");
            
            client.println("</body></html>");

            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}


void displayON(){
  tft.setTextSize(3);
  tft.setRotation(3);
  displayText("Hello...!", ST77XX_YELLOW,60,40);
}


void displayOFF(){
  tft.setTextSize(3);
  tft.setRotation(3);
  displayText("Bye..!", ST77XX_CYAN,60,40);
  delay(1000);
  tft.fillScreen(ST77XX_BLACK);
  digitalWrite(BackLight, LOW);
}

void displayText(String text, uint16_t color, int x, int y) {
  digitalWrite(BackLight, HIGH);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
