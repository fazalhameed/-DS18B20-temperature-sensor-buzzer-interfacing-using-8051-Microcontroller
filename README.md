# -DS18B20-temperature-sensor-buzzer-interfacing-using-8051-Microcontroller

## Overview:
This project involves interfacing a DS18B20 temperature sensor and a passive buzzer with an 8051 microcontroller unit (MCU). The MCU reads the temperature, displays it on LCD and 7-segment displays with decimal point precision, and triggers the buzzer if the temperature exceeds a user-defined threshold (default threshold set at 37°C).

## Key Features:
- **Sensor Driver:**
  Implements a driver for the DS18B20 sensor to facilitate communication with the MCU.
- **Temperature Reading:** 
  Utilizes a timer interrupt to read the temperature from the sensor every second.
- **Display:** 
   Shows the temperature on an LCD and 7-segment displays concurrently, including the decimal part of the reading.
- **Buzzer Control:**
   Activates the passive buzzer in a specified pattern (ON for 500 ms, OFF for 500 ms) if the temperature surpasses the set threshold.
- **Serial Communication:** 
   Allows users to send the temperature threshold value from an external device (e.g., computer) to the MCU via serial port. The buzzer sounds if the temperature reading exceeds this threshold.

## Safety Considerations:
 **Temperature Limits:** Warns against exceeding safe temperature limits (37°C) from sources like body heat or match sticks. Recommends using a lighter for higher temperatures to avoid risks like burns or odor.

## Usage:
1. Connect the DS18B20 sensor, passive buzzer, LCD, and 7-segment display to the 8051 MCU following the provided wiring diagram.
2. Compile and upload the MCU code containing the driver, temperature reading logic, display functions, buzzer control, and serial communication handling.
3. Use a terminal or software to communicate with the MCU via serial port and set the temperature threshold value.
4. Observe the temperature readings displayed on the LCD and 7-segment display. If the temperature exceeds the set threshold, the buzzer will activate as per the specified pattern.

