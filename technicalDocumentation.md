# Technical Documentation

## Arduino

### Boards used 
- Arduino Nano every
- Arduino Uno R4 Wifi
- Elegoo Nano

### Libraries 

| Relevant Device | Library Names | Include call | Author | Desciption |
|----|----|----|----|------|
| IIC devices | Wire | <Wire.h> | Arduino ? | used for IIC work |
| BME280 Temp, pressure, and humidity sensor | Adafruit_BME280_Library | <Adafruit_BME280.h> | Adafruit | used for the BME280 Temperature, Pressure, and Humnidity sensor |
| Adafruit Sensors and Clones | Adafruit Unifed Sensor | <Adafruit_Sensor.h> | Adafruit | Unified library ? | Adafruit Unified Sensor Driver |
| BH1750 Light Sensor | Light Sensor | <BH1750.h> | Christopher Laws | |
| QM5883 Sensors |QMC5883LCompass| <QMC5883LCompass.h> | MPrograms | 3-axis magnetometer library  | 
| 0.96" OLED Screen | Adafruit SSD1306 | |  Adafruit | OLED driver library for small screens | 
| 0.96" OLED Screen | Adafruit GFX library | | Adafruit | core graphics library for Adafruit displays| 



## Electrosmith Daisy 


## Sensors
### Sensor details
All chage frequencies, domain variabilities, and values are adjustable by code and installation design.

| Sensor | Frequency of Change | Domain of Variability | Likley Values | Notes |
|--------|---------------------|-----------------------|---------------|-------|
| Capacitive Touch | Frequent | capacitance registers as a number and touching modifies that number | 300's | 12 contacts map to 12 notes in an octave |
| Light | Very Low | similar to capacitive touch but with very large swing depending on proximity of strength and proximity of light sources | | Lux is a non-linear parameter |
| Temperature | Very Low | Very Low | 24+/- 10 | Perhaps create a tube you can blow into ? |
| Humidity | Very Low | Very Low | | |Perhaps create a tube you can blow into ? |
| Magnetic Field X, Y, & Z | Very Low | | | 360 degrees of rotation | Signal to noise ratio for detecting nearby electronics is likley too low - providing Magnetic objects or mounting sensor to a moving object will increase utility |
| PIR | High | Binary Data | Binary Data | 
| Buttons | High | Binary Data | Binary Data |
| Potentiometers | High | Full Range |

### Sensor Technical Data

| Sensor ID | Other IDs          | Sensor Name         | Operational Voltage | I²C address |
|-----------|--------------------|---------------------|---------|------|
| BH1750    |                    | Light               | 3–5V    | 0x23 |
| MPR121   |                    | Capacitive Touch    | 3.3V    |      |
| BME280   | BMP280             | Temp / Pressure / Humidity | 5V | 0x76 |
| HW246    | QMC5883L, GY121    | Magnetic Field      | 3–5V    | 0x0D |


## Other components
 
 # 0.96 Inch OLED Display Screen Module
Note: The 7-bit I2C address of the 0.96-inch OLED screen is 0111100 (0x3C). 0x78 in the PCB is 0111100, and the 8th bit represents the "write" operation. If the code only specifies the I2C slave device address, use the 7-bit binary code (such as 0x3C).

    Display Type: OLED (Organic Light Emitting Diode)
    Resolution: 128x64 pixels
    Interface: I2C Operating Voltage: 3.3V - 5V
    Minimum Visible Angle: 160 Degree
    Energy Consumption (Normally): 0.06w
    View Angle：>160°
    Diyplay Dimensions: 0.91 inches (diagonal)
    Working Temperature: -20°C to 60°C
    Driver IC: SSD1306 Displya
    Color: Blue and Yellow

# WWZMDiB Micro SD TF Card Adapter Reader Module with Logic Level Chip 3.3V 5V 6 Pin SPI Interface
    Micro SD Card Module: The module includes 74HC125 and AMS1117 chips, enabling voltage level conversion between 3.3V and 5V systems, ensuring stable communication between the Micro SD card and host devices with different voltage levels.
    Interface level: 3.3V or 5V
    Supported Interface: SPI
    Supported Card Type: Micro SD Card (TF Card)
    Socket: Pop-up

## Pure Data
