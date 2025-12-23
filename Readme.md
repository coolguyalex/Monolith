# Monolith Readme

## Introduction

Monolith is a sensor-driven real-time sonification and datalogging sculptural project.
Monolith is designed to record environmental data through a diverse sensor suite enabling follow-on sicence and art. 
The projects goals are:
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
