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
All chage frequencies, domain variabilities, and values are adjustable by code and installation design.

| Data Stream | Sensor | Frequency of Change | Domain of Variability | Likley Values | Notes |
|-------------|--------|---------------------|-----------------------|---------------|-------|
| Capacitive Touch | MPR121 |Frequent | capacitance registers as a number and touching modifies that number | 300's | 12 contacts map to 12 notes in an octave |
| Light | | BH1750 | Very Low | Digital similar to capacitive touch but with very large swing depending on proximity of strength and proximity of light sources | | Digital Lux is a non-linear parameter |
| Temperature | BME280 | Very Low | Very Low | 24+/- 10 | Digital Perhaps create a tube you can blow into ? |
| Humidity |  BME280 |Very Low | Very Low | | | Digital Perhaps create a tube you can blow into ? |
| Pressure |  BME280 | Extremely Low | Extremeley Low | Digital Think of a way to make this change more noticable? |
| Magnetic Field X, Y, & Z | QMC5883L | Very Low | | | 360 degrees of rotation | Digital Signal to noise ratio for detecting nearby electronics is likley too low - providing Magnetic objects or mounting sensor to a moving object will increase utility |
| PIR | HC-SR501 |  High | Binary Data | Digital Binary Data | 
| Buttons | High | Binary Data | Digital Binary Data |
| Potentiometers | High | Analog Full Range |

### Component Technical Data

| Sensor ID | Other IDs          | Sensor Name         | Operational Voltage | I²C address |
|-----------|--------------------|---------------------|---------|------|
| BH1750    |                    | Light               | 3–5V    | 0x23 |
| MPR121   |                    | Capacitive Touch    | 3.3V    | 0x5A     |
| BME280   | BMP280             | Temp / Pressure / Humidity | 5V | 0x76 |
| HW246    | QMC5883L, GY121    | Magnetic Field      | 3–5V    | 0x0D |
| SSD1306| | 0.96" OLED Display | 5V | 0x3C |

Monlith is a project by Alexander Sousa.
