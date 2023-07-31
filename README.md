# ESPi_Software

<img src ="https://github.com/sbcshop/ESPi_Software/blob/main/images/ESPi%20Banner.jpg">

ESPi, with its powerful ESP32 and Ethernet, is the ideal answer for your networking requirements. Along with WiFi, this board supports a variety of internet protocols, including TCP, UDP, WOL over UDP, ICMP, IPv4, and others. 
This repository contains a step-by-step guide for getting started with the ESPi board.

### ESPi Features:
- Powered by ESP32-WROOM-32
- ESP32 Multipurpose GPIO pins breakout for Additional peripheral interfacing
- 1.14" TFT display for visual interaction
- 5-way joystick for adding more control features for project
- SPI, I2C, UART interfacing
- Onboard RJ45 with Transformer Ethernet Port
- Support 4 independent SOCKETs simultaneously 
- Support Hardwired TCP/IP Protocols : TCP, UDP, ICMP, IPv4, ARP, IGMP, PPPoE
- Ethernet power down mode and Wake on LAN over UDP for energy-saving
- 10Base-T/100Base-TX Ethernet PHY with auto-negotiation for full and half duplex with 10 and 100-based connections
- Network indicator LEDs for full/half duplex, link, 10/100 speed, and active status
- Type C interface for programming and powering board
- Status Led for power
- Onboard Boot and reset button

### ESPi Specifications:
- ESP32-WROOM-32 is a powerful, generic Wi-Fi + Bluetooth® + Bluetooth LE MCU
- WiFi 802.11 b/g/n (802.11n up to 150 Mbps) support
- Bluetooth v4.2 BR/EDR and Bluetooth LE specification
- Display Resolution 240x135
- IPS Display 65K RGB Colors 
- SPI Interface with ST7789 Display Driver
- Ethernet Network Performance: Max.25Mbps
- Ethernet TX/RX Buffer : 16KB
- Operating temperature: -40°C to +85°C
  
## Getting Started with ESPi
### Pinout
<img src="https://github.com/sbcshop/ESPi_Software/blob/main/images/ESPi_Pinout.jpg">

- (1) RJ45 Ethernet
- (2) 1.14” Display
- (3) 5-way Joystick
- (4) ESP32-WROOM-32
- (5) & (9) Multipurpose GPIOs breakout
- (6) Type C 
- (7) BOOT Button
- (8) RESET Button


### Interfacing Details
- Ethernet interfacing with ESP32
  
  | ESP32 | Ethernet | Function |
  |---|---|---|
  | GP18 | SCLK | Clock pin of SPI interface for Ethernet|
  | GP23 | MOSI/A0 | MOSI (Master OUT Slave IN) pin of SPI interface|
  | GP19 | MISO/A1 | MISO (Master IN Slave OUT) pin of SPI interface|
  | GP5 | CSn | Chip Select pin of SPI interface|
  
- Display interfacing with ESP32

  | ESP32 | Display | Function |
  |---|---|---|
  | GP14 | SCK | Clock pin of SPI interface for Display |
  | GP13 | DIN | MOSI (Master OUT Slave IN) pin of SPI interface |
  | GP15 | CS  | Chip Select pin of SPI interface |
  | GP27 | DC  | Data/Command pin of SPI interface |
  | GP26 | RES | Display Reset pin |
  | GP4  | BL  | Backlight of display |

- Joystick and button interfacing with ESP32

  | ESP32 | Hardware |
  |---|---|
  | GP25 | Joystick Selection |
  | GP33 | Joystick Down | 
  | GP32 | Joystick Up |
  | GP35 | Joystick Left | 
  | GP34 | Joystick Right | 
  | BL   | Boot Button |
  
- Breakout GPIOs

  Breakout 1
  | ESP32 | Type* | Function |
  |---|---|---|
  |GP12 | I/O | GPIO12, ADC2_CH5, TOUCH5, RTC_GPIO15, MTDI, HSPIQ, HS2_DATA2, SD_DATA2, EMAC_TXD3 |
  |GP2  | I/O | GPIO2, ADC2_CH2, TOUCH2, RTC_GPIO12, HSPIWP, HS2_DATA0, SD_DATA0 |
  |GP36 | I | GPIO36, ADC1_CH0, RTC_GPIO0 |
  |GP39 | I | GPIO39, ADC1_CH3, RTC_GPIO3 |
  |GND  | P | Ground pin |
  |3V3  | P | Positive Supply 3.3V |
  
  Breakout 2
  | ESP32/Ethernet | Type* | Function |
  |---|---|---|
  |GP16 |  I/O | GPIO16, HS1_DATA4, U2RXD, EMAC_CLK_OUT |
  |GP17 |  I/O | GPIO17, HS1_DATA5, U2TXD, EMAC_CLK_OUT_180 |
  |GP22 |  I/O |GPIO22, VSPIWP, U0RTS, EMAC_TXD1 |
  |ET_INT | - | Ethernet Interrupt pin |
  |GP21 | I/O | GPIO21, VSPIHD, EMAC_TX_EN |
  |ET_RST | - | Ethernet Reset pin |  

  *I-INPUT, O-OUTPUT, P-POWER & T-HIGH IMPEDENCE


Play with it and create your own, **Happy Coding!** 


### Resources:
  - [ESPi Schematic](https://github.com/sbcshop/ESPi_Hardware/blob/main/Design%20Data/SCH%20ESPi.pdf)
  - [Product Hardware Files](https://github.com/sbcshop/ESPi_Hardware)
  - [Product Step File](https://github.com/sbcshop/ESPi_Hardware/blob/main/Mechanical%20Data/ESPi.step)
  - [Getting Started with ESP32 in Arduino](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
  - [Arduino IDE 1 overview](https://docs.arduino.cc/software/ide-v1/tutorials/Environment)
  - [ESP32 Wroom 32 Datasheet](https://github.com/sbcshop/ESPi_Software/blob/main/documents/esp32-wroom-32_datasheet_en.pdf)
  - [Wiznet Datasheet](https://github.com/sbcshop/ESPi_Software/blob/main/documents/w5100s-q_datasheet.pdf)
  - [Wiznet References]( https://www.wiznet.io/product-item/w5100/)

## Related Products
- **[NetPi](https://shop.sb-components.co.uk/products/netpi-ethernet-hat-for-raspberry-pi-pico)** : HAT with onBoard Ethernet support can be powered by Raspberry Pi Pico / Pico W

   ![NetPi](https://shop.sb-components.co.uk/cdn/shop/files/03_439625d0-e0d2-4555-b3b3-5d8fa316d7d8.jpg?v=1683535354&width=200)

- **[Touchsy](https://shop.sb-components.co.uk/products/squary?variant=40443840921683)** : 3.2" Touch LCD Display Based on ESP32 MCU

   ![Touchsy](https://shop.sb-components.co.uk/cdn/shop/files/esp.jpg?v=1686900424&width=200)

- **[Ardi-32](https://shop.sb-components.co.uk/products/encropi?_pos=1&_sid=95f822d26&_ss=r)** : Uno R3 Alternative Board Based on ESP32-S3-WROOM-1

   ![Ardi-32](https://shop.sb-components.co.uk/cdn/shop/files/ardi322.jpg?v=1688468126&width=200)
  
## Product License

This is ***open source*** product. Kindly check the LICENSE.md file for more information.

Please contact support@sb-components.co.uk for technical support.
<p align="center">
  <img width="360" height="100" src="https://cdn.shopify.com/s/files/1/1217/2104/files/Logo_sb_component_3.png?v=1666086771&width=350">
</p>
