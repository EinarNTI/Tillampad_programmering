# Tillampad_programmering
# Clock and Temperature Display Project

### Author: Einar Söderberg Beckman  
### Date: October 11, 2024

## Project Overview

This project creates a clock and temperature monitoring system using an **RTC module (DS3231)** for timekeeping, an **OLED display (1306)** to show time and temperature, an **analog temperature sensor** for real-time temperature readings, and a **9g servo motor** to display the temperature range. Additionally, it includes a **piezo buzzer** for an alarm feature, which can be set or adjusted using two buttons.

## Features

1. **Time Display**: Utilizes the DS3231 RTC module to keep track of the time and displays it on the OLED.
2. **Temperature Monitoring**: Reads analog input from a temperature sensor and converts it to Celsius.
3. **Servo Motor Control**: Maps the current temperature to a servo motor position, visually indicating the temperature range.
4. **Alarm System**: A piezo buzzer sounds an alarm at a set time. The alarm time is adjustable using two push buttons.
5. **OLED Display**: Shows current time, temperature, and alarm time.

## Hardware Setup

- **RTC Module (DS3231)** connected via I2C for timekeeping.
- **OLED Display (SSD1306)** connected via I2C to display time, temperature, and alarm time.
- **Analog Temperature Sensor** connected to analog pin (A0) for reading temperature.
- **Servo Motor (9g)** connected to digital pin 2 to display temperature range.
- **Piezo Buzzer** connected to analog pin (A1) for alarm sound.
- **Buttons** for increasing and decreasing the alarm time connected to digital pins 13 and 12.

## Code Components

### Libraries

- `RTClib.h` - Library for interfacing with DS3231.
- `Wire.h` - Library for I2C communication.
- `U8glib.h` - Library for OLED display.
- `Servo.h` - Library for controlling the servo motor.

### Functions

1. **`setup()`**: Initializes serial communication, hardware modules, and configures pins. Sets initial time and alarm time.
  
2. **`loop()`**: Main loop, which updates the OLED display, moves the servo, adjusts the alarm if necessary, and checks the current time against the alarm time.

3. **`getTime()`**: Reads the current time from the DS3231 RTC and formats it as `hh:mm:ss`.

4. **`getTemp()`**: Reads the analog input from the temperature sensor and calculates the temperature in Celsius.

5. **`oledWrite()`**: Displays the current time, temperature, and set alarm time on the OLED display.

6. **`servoWrite()`**: Maps the temperature value to the servo position, where the motor moves according to the temperature range (10-30 °C).

7. **`alarm()`**: Activates the piezo buzzer when the current time matches the set alarm time.

8. **`alarmAdjust()`**: Adjusts the alarm time in 5-minute increments when either increase or decrease button is pressed. Ensures the time wraps around when going below 0:00 or above 23:59.

## Usage

1. **Alarm Setting**: Use the two buttons to set the alarm time by increasing or decreasing the alarm time in 5-minute increments.
2. **Display Updates**: The OLED display automatically updates with the current time, temperature, and alarm time.
3. **Temperature Indicator**: The servo motor adjusts according to the temperature range, giving a physical representation of the temperature.
4. **Alarm Sound**: At the set alarm time, the piezo buzzer activates for one second.

## Dependencies

Install the following Arduino libraries before uploading the code:

- RTClib
- Wire
- U8glib
- Servo