# RAM-with-Arduino
> Create your RAM with basics components and your Arduino

## Table of Contents
* [General Information](#general-information)
* [Technologies And Materials Used](#technologies-and-materials-used)
* [Features](#features)
* [Setup](#setup)
* [Usage](#usage)
* [Project Status](#project-status)
* [License](#license)


## General Information
Following the [schematic](Schematic.pdf) you can create your RAM using only capacitors and resistors. The Arduino is the brain of the project and its role is to write, read and refresh the data in your RAM. With the help of a button, you can also read the content of your RAM on the serial monitor of the Arduino IDE.


## Technologies And Materials Used
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
- Create the circuit described in the [schematic](Schematic.pdf)
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

You can also find an example on how to do something more with you RAM in the [RAM-Example folder](RAM-Example) where the script writes something new in the RAM every 5 seconds after checking that the RAM contains the correct informations


## Project Status
The project is complete


## License
The source code for the site is licensed under the [MIT license](LICENSE)
