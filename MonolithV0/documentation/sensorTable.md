# Sensor Data Table
| Sensor | Frequency of Change | Domain of Variability | Likley Values | Notes|
|------------------|----------|---------------------------------------------------------------------|-------|------------------------------------------|
| Capacitive Touch | Frequent | capacitance registers as a number and touching modifies that number | 300's | 12 contacts map to 12 notes in an octave |
| Light | Very Low (possibly frequent with light source and instructions) | similar to capacitive touch but with very large swing depending on proximity of strength and proximity of light sources | Lux is a non-linear parameter |
| Temperature | Very Low | Very Low | Perhaps create a tube you can blow into ? |
| Humidity | Very Low | Very Low | Perhaps create a tube you can blow into ? |
| Magnetic Field X, Y, & Z | Very Low | 360 degrees of rotation | Signal to noise ratio for detecting nearby electronics is likley too low - providing Magnetic objects or mounting sensor to a moving object will increase utility |
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
