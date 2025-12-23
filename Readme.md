# Monolith Readme

## Introduction

Monolith is an open-source, sensor-driven, real-time, sonification and datalogging sculptural project designed to enable follow-on sicence, art, and commuinity engagement. 
Project Monolith seeks to:
- Sonify data by feeding information to a generative (non-AI) synthesis and composition program. 
- Provide local environmental datasets to researchers.
- Use public art to connect people with their local environments.
- Generate appreciation for nature by blurring the lines between natural cycles, data, and art.

## Technical details
Monolith utilizes arduino and similar microcontroller platforms to collect and log sensory data.
Micrcontroller code has thus far all been built in the arduino language. 
Data is then passed to sonification programs built in Puredata. 
Thusa far, puredata patches are run on a windows laptop and data is passed via serial connection. 
Puredata externals: iemlib and comport externals have been used in iterations in which Pd runs on a PC. 
In other iterations puredata is compiled onto an electrosmith daisy microcontroller and data is passed between arduino and daisy via voltage. 
Transferring data via serial UART will likley be necessary when high volumes of data are passed in future iterations. 

### Sensor details
All frequencies (and to a lesser extent, Domains ) could be adjusted to be proportionate to interation based on installation design.

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

| Sensor ID | Other names        | Sensor Name         | Voltage | I²C  |
|-----------|--------------------|---------------------|---------|------|
| BH1750    |                    | Light               | 3–5V    | 0x23 |
| MPR121   |                    | Capacitive Touch    | 3.3V    |      |
| BME280   | BMP280             | Temp / Pressure / Humidity | 5V | 0x76 |
| HW246    | QMC5883L, GY121    | Magnetic Field      | 3–5V    | 0x0D |


Monlith is a project by Alexander Sousa.
