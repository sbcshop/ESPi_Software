/******************************************************************************************************
 * Demo code to test onboard 5-Way Joystick of ESPi Board
 *
 * For more code examples of ESPi board: https://github.com/sbcshop/ESPi_Software/tree/main/examples
 ******************************************************************************************************/

const int upBtn = 32;  
const int downBtn = 35; 
const int leftBtn = 34; 
const int rightBtn = 33; 
const int centreBtn = 25;

void setup(void) {
  Serial.begin(115200); // configure serial communication 
  // Set Joystick switch connected to ESP32 GPIO pins as INPUT
  pinMode(upBtn, INPUT); 
  pinMode(downBtn, INPUT);
  pinMode(rightBtn, INPUT);
  pinMode(leftBtn, INPUT);
  pinMode(centreBtn, INPUT);

  Serial.println("****** 5-Way Joystick Testing *******");
}

void loop() {
  byte up, down, right, left, centre;
  // read the values of switch, normally HIGH, LOW when switch pressed
  up = digitalRead(upBtn); 
  down = digitalRead(downBtn);
  right = digitalRead(rightBtn);
  left = digitalRead(leftBtn);
  centre = digitalRead(centreBtn);

  Serial.println("Button Value:");
  Serial.printf("up:%d down:%d left:%d right:%d centre:%d \n ", up, down, left , right, centre);

 
  if (up == 0){
    Serial.println("UP BTN Pressed!");
    delay(50);
  }

  if (left == 0) {
    Serial.println("Left BTN Pressed!");
    delay(50);
  }

  delay(1000);
}
