# RAM-with-Arduino
> Create your RAM with basics components and your Arduino

## Table of Contents
* [General Information](#general-information)
* [Materials Used](#materials-used)
* [Features](#features)
* [Usage](#usage)
* [License](#license)


## General Information
Following the [schematic](Schematic.pdf) you can create your RAM using only capacitors and resistors. The Arduino is the brain of the project, and its role is to write, read, and refresh the data in your RAM. With the help of a button, you can also read the content of your RAM on the serial monitor of the Arduino IDE.


## Materials Used
- Arduino UNO - Rev3
- Capacitors - 10μF
- Resistors - 1000Ω
- Button
- Resistor - 10000Ω
- Jumper cables


## Features
- Create a RAM with as many bits as your board allows.
- Read and write your data on something that you created.
- Let the software prevent you from losing your data because of capacitor leakage with periodic refreshing.


## Usage
You can change the number of bits, the value of capacitors and resistors (as long as they have consistent values), and the initial values written on the RAM.
If you decide to change these parameters, you will also need to change them in the code:

```
const double CAPACITOR_VALUE = 10E-6;  ---> Capacitor value in Farads

const double RESISTOR_VALUE = 1E3;  ---> Resistor value in Ohms

int bitDigitalPins[] = {2, 3, 4};  ---> digital pins that write the value

int bitAnalogPins[] = {A0, A1, A2};  ---> analog pins that read the charge

int writeValues[] = {1, 0, 1};  ---> The values you want to write

BitHandler bits[3];   ---> The number of bits in your configuration
```

You can also find an example of how to make use of your RAM in the [RAM-Example folder](RAM-Example) where the script writes something new in the RAM every 5 seconds after checking that the RAM contains the correct information.


## License
The source code for the site is licensed under the [MIT license](LICENSE).
