# Wiring Reference

## MPU6050

| MPU6050 | Arduino Uno |
|---|---|
| SDA | A4 |
| SCL | A5 |
| GND | GND |
| VCC | Module-compatible supply |

## LED

```text
LED → D13
```

For an external LED, use a suitable series resistor.

## Buzzer

```text
Buzzer + → D8
Buzzer - → GND
```

Use a transistor driver if the buzzer requires more current than an Arduino GPIO can safely provide.

## Confirmation Button

```text
Button one side → D2
Button other side → GND
```

The code uses `INPUT_PULLUP`, so no external pull-up resistor is required.

## Notes

The MPU6050 communicates with the Arduino Uno using I2C:

```text
SDA → A4
SCL → A5
```

The motion threshold should be calibrated after mounting the sensor.
