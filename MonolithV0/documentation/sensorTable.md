# Sensor Table
|Sensor|Frequency of Change|Domain of Variability|Notes|
|------------------|----------|-------------------------------------------------------------|-----|
| Capacitive Touch | Frequent | capacitance registers as a number and touching modifies that number | Linear |
| Light | Very Low (possibly frequent with light source and instructions) | similar to capacitive touch but with ver large swing depending on proximity of strength and proximity of light sources | Lux is a non-linear quantity |
|Temperature | Very Low |
| Humidity | Very Low |
| Magnetic Field X, Y, & Z | Very Low unless magnets provided or mounted to a moving object | 360 degrees of rotation | Signal to noise ratio for detecting nearby electronics is likley too low |
| PIR | High | Binary Data |
| Buttons | High | Binary Data |
| Potentiometers | High | Full Range |

## Sensor Technical Data

| Sensor ID | Other names        | Sensor Name         | Voltage | I²C  |
|-----------|--------------------|---------------------|---------|------|
| BH1750    |                    | Light               | 3–5V    | 0x23 |
| MPR121   |                    | Capacitive Touch    | 3.3V    |      |
| BME280   | BMP280             | Temp / Pressure / Humidity | 5V | 0x76 |
| HW246    | QMC5883L, GY121    | Magnetic Field      | 3–5V    | 0x0D |
