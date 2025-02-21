# Tillampad_programmering

# Stabilized Plane Project

**Author:** Einar Söderberg Beckman  
**Date:** 2025-02-07  

## Overview
This project uses two servo motors and an MPU6050 accelerometer to create a stabilized platform or plane. The servos adjust based on the accelerometer's measurements to maintain balance.

## Components
- **Servo Motors:** Two servo motors control the X and Y axes. (A third servo, `zServo`, is declared but not currently used.)
- **MPU6050 Accelerometer:** Captures acceleration and gyroscopic data.
- **Arduino Board:** Acts as the controller.

## Libraries Used
- `Servo.h` for controlling servo motors  
- `Adafruit_MPU6050.h` and `Adafruit_Sensor.h` for interfacing with the MPU6050 sensor

## Wiring
- **X-Axis Servo:** Pin 2  
- **Y-Axis Servo:** Pin 3  
- **Z-Axis Servo:** Pin 4 (Unused)  
- **MPU6050:** Connected via I2C (SDA, SCL pins on Arduino)

## How It Works
1. The MPU6050 collects data on the plane's orientation.
2. Gyroscopic readings are converted from radians to degrees.
3. Averages of the readings are calculated using arrays to smooth out fluctuations.
4. The X and Y servos adjust their angles based on these averages.

## Code Structure
- **Setup:** Initializes serial communication, attaches servos, and configures the sensor.
- **Loop:** Continuously reads data, calculates angles, and moves servos.
- **`averageX()` & `averageY()`:** Store readings in arrays and return averaged values.

## Installation and Usage
1. Install the required libraries via the Arduino Library Manager:
    - `Servo`
    - `Adafruit MPU6050`
    - `Adafruit Sensor`
2. Connect the components as described.
3. Upload the provided code to your Arduino board.
4. Open the Serial Monitor to check sensor status.

## License
This project is open-source. Feel free to modify and distribute.

## Acknowledgments
- Adafruit for sensor libraries
- Arduino community for inspiration


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
