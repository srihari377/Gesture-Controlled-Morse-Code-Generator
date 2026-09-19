# Gesture-Controlled Morse Code Generator

An Arduino Uno-based gesture-controlled Morse code generator using an MPU6050 motion sensor, LED and buzzer feedback.

> **Important:** The source code in this repository is a reconstructed reference implementation based on the documented project architecture. It is not the original source code used in the original prototype.

## Overview

The project detects hand movements using an MPU6050 accelerometer/gyroscope and maps the movement duration to Morse-code symbols.

- Short movement → Dot `.`
- Long movement → Dash `-`
- LED → visual feedback
- Buzzer → audio feedback
- Push button → confirms and decodes the current Morse character

## Hardware

- Arduino Uno
- MPU6050 accelerometer/gyroscope
- LED
- Buzzer
- Push button for character confirmation

## Technologies

- Arduino Uno
- MPU6050
- C/C++
- I2C
- Embedded Systems

## Pin Connections

| Component | Arduino Uno |
|---|---|
| MPU6050 SDA | A4 |
| MPU6050 SCL | A5 |
| MPU6050 GND | GND |
| MPU6050 VCC | Module-compatible supply |
| LED | D13 |
| Buzzer | D8 |
| Confirm button | D2 |

The button is connected between D2 and GND. The code uses the Arduino's internal pull-up resistor.

## How It Works

### 1. Motion detection

The MPU6050 continuously measures acceleration.

### 2. Dot or dash

The duration of the detected movement determines the Morse symbol:

```text
Short movement → .
Long movement  → -
```

### 3. Character formation

Symbols are collected into a Morse sequence.

For example:

```text
.-
```

represents:

```text
A
```

### 4. Character confirmation

Pressing the confirmation button tells the Arduino to decode the current Morse sequence.

### 5. Feedback

The LED and buzzer provide immediate feedback for each detected symbol and decoded character.

## Example

```text
Short movement
Long movement
Button press
```

Output:

```text
.- → A
```

## Morse Table

| Letter | Morse |
|---|---|
| A | .- |
| B | -... |
| C | -.-. |
| D | -.. |
| E | . |
| F | ..-. |
| G | --. |
| H | .... |
| I | .. |
| J | .--- |
| K | -.- |
| L | .-.. |
| M | -- |
| N | -. |
| O | --- |
| P | .--. |
| Q | --.- |
| R | .-. |
| S | ... |
| T | - |
| U | ..- |
| V | ...- |
| W | .-- |
| X | -..- |
| Y | -.-- |
| Z | --.. |

## Arduino Setup

1. Open `Gesture_Morse_Code.ino` in Arduino IDE.
2. Select **Arduino Uno**.
3. Select the correct COM port.
4. Connect the hardware.
5. Upload the sketch.
6. Open Serial Monitor at **9600 baud**.
7. Perform short and long hand movements.
8. Press the confirmation button to decode a character.

## Calibration

The motion threshold and dot/dash duration may need adjustment for the actual prototype:

```cpp
MOTION_THRESHOLD
DOT_DASH_THRESHOLD
```

## Applications

- Assistive communication
- Gesture-based interfaces
- Morse-code learning
- Low-cost communication systems
- Embedded systems projects

## Future Improvements

- OLED display for live Morse output
- Complete word/sentence composition
- Wireless communication
- Mobile app integration
- Text-to-speech output
- Custom gesture calibration

## Project Structure

```text
Gesture-Controlled-Morse-Code-Generator/
├── Gesture_Morse_Code.ino
├── README.md
└── hardware/
    └── wiring.md
```
