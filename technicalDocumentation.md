# Technical Documentation

## Arduino

### Boards used 
- Arduino Nano every
- Arduino Uno R4 Wifi
- Elegoo Nano

### Libraries 
<Wire.h>
<Adafruit_BME280.h> by Adafruit
<Adafruit_Sensor.h>
<BH1750.h> by Christopher Laws
<QMC5883LCompass.h> by MPorgrams

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
Specifications:

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
    3PCS Pack: 0.96 Inch Disyplay Module x 3 Female to Female Dupont Wire x 5 Male to Female Dupont Wire x 5
    6PCS Pack: 0.96 Inch Disyplay Module x 6 Female to Female Dupont Wire x 5 Male to Female Dupont Wire x 5



## Pure Data
