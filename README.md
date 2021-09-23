# RAM-with-Arduino
> Create your RAM with basics components and yout Arduino

## Table of Contents
* [General Information](#general-information)
* [Technologies Used](#technologies-used)
* [Features](#features)
* [Setup](#setup)
* [Usage](#usage)
* [Project Status](#project-status)
* [License](#license)


## General Information
Following the schematic in the pdf file you can create your RAM using only capacitors and resistors. The Arduino is the brain of the project and its role is to write, read and refresh the data in your RAM. With the help of a button, you can also read the content of your RAM on the serial monitor of the Arduino IDE.


## Technologies Used
- Arduino IDE - version 1.8.16
- Arduino UNO - Rev3
- Capacitors - 10μF
- Resistors - 1000Ω
- Button
- Resistor - 10000Ω
- Jumper cables


## Features
- Create a RAM with as many bits your board allows
- Read and write your data on something that you created
- Let the software make you not loose your data beacuse of capacitor leakage


## Setup
- Choose your Arduino Board of choice
- Create the circuit described in the pdf file
- Upload the code to your Arduino


## Usage
You can change the number of bits, the value of capacitors and resistors (as long as they are the same on the RAM) and the initial values written on the RAM.
If you decide to change these things, you will also need to change them in the code:

`const double CAPACITOR_VALUE = 10E-6;  ---> Capacitor value in Farad`

`const double RESISTOR_VALUE = 1E3;  ---> Resistor value in Ohm`

`int bitDigitalPins[] = {2, 3, 4};  ---> digital pins that write the value`

`int bitAnalogPins[] = {A0, A1, A2};  ---> analog pins that read the charge`

`int writeValues[] = {1, 0, 1};  ---> The values you want to write`

`BitHandler bits[3];   ---> The number of bits in your configuration`


## Project Status
The project is complete


## License
The source code for the site is licensed under the MIT license
