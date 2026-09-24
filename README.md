# WatchOutMilk

A boiling-milk overflow indicator. A K-type thermocouple in the milk measures its temperature, and the device beeps and lights up LEDs as the milk heats, then sounds a continuous alarm just before it boils over.

I started this in October 2020, during the COVID-19 lockdown, when I was in 10th grade, because milk boiling over was a repeated problem at home. **Version 1** (Arduino Nano) is complete and was tested on real milk. **Version 2** (XIAO ESP32-C3, custom PCB, 3D-printed enclosure) is a work in progress.

---

## Repository structure

```
WatchOutMilk/
├── Version 1/
│   ├── Code/
│   │   ├── Version1_Prototype/  # First prototype sketch (SH1106 OLED + 4 LEDs)
│   │   ├── Version1_LCD/        # 16x2 I2C LCD version
│   │   └── Version1_OLED/       # SH1106 OLED + 4 LEDs version
│   ├── PCB Gerber/            # Gerber files for the V1 PCB (EasyEDA)
│   └── Milk_Temperature.apk   # Android app (MIT App Inventor) - abandoned, see below
├── LICENSE                    # MIT
└── README.md
```

Version 2 files will be added once they're ready.

---

## Version 1 (Oct 2020 – Feb 2021) — Completed

### How it works
The MAX6675 reads the thermocouple and sends the temperature to an Arduino Nano over SPI. The Nano then:
- beeps briefly at **50, 60, 70, 80, and 90 °C**,
- sounds a **continuous alarm at ≥ 98 °C**,
- lights LEDs cumulatively at **60 (blue), 70 (green), 80 (yellow), and 90 °C (red)** (OLED version),
- shows the temperature in °C and °F on a 16x2 I2C LCD or an SH1106 128x64 OLED.

### Hardware
| Component | Part |
|---|---|
| Microcontroller | Arduino Nano V3.0 |
| Thermocouple amplifier | MAX6675 breakout |
| Sensor | K-type thermocouple |
| Display | 16x2 I2C LCD (0x27) **or** SH1106 128x64 I2C OLED |
| Alerts | Buzzer + 4 LEDs (blue, green, yellow, red) with resistors |
| PCB | Custom 2-layer board designed in EasyEDA (Gerbers in `Version 1/PCB Gerber/`) |

### Pinout (Arduino Nano)
The pinout is different in the prototype sketch, so check which sketch you're using.

| Signal | `Version1_LCD` / `Version1_OLED` | `Version1_Prototype` |
|---|---|---|
| MAX6675 SO / CS / SCK | D3 / D4 / D5 | D5 / D4 / D3 |
| MAX6675 VCC / GND | D6 / D7 (GPIO-powered) | 5V / GND rails (see note) |
| Buzzer + / − | D8 / D9 | D7 / D6 |
| Display SDA / SCL | A4 / A5 | A4 / A5 |
| LED Blue | D11 (+) / D10 (−) | D10 |
| LED Green | D13 (+) / D12 (−) | D9 |
| LED Yellow | A3 (+) / A2 (−) | D11 |
| LED Red | A1 (+) / A0 (−) | D12 |
| LED common ground | — (each LED has its own − pin) | D8 |
| Bluetooth module VCC | D2 | D13 |

LEDs are only in the OLED and prototype sketches. **Note:** the prototype sketch declares `ThermoVCC = 2` but never sets that pin as an output, so the MAX6675 needs to be powered from the 5V rail with this sketch.

### Libraries
- `max6675` (Adafruit MAX6675 library)
- `Wire`
- `LiquidCrystal_I2C` (LCD version)
- `U8glib` (OLED version)

### Running it
1. Install the libraries above in the Arduino IDE.
2. Open one of the sketches from `Version 1/Code/`.
3. Select **Arduino Nano** as the board and upload.
4. Open the Serial Monitor at **9600 baud** to see the raw temperature readings.

### About the Android app
`Milk_Temperature.apk` was built in MIT App Inventor to connect to an HC-05 Bluetooth module, show the live temperature, and play an alarm above 97 °C. I dropped it because the Bluetooth connection was unreliable, and because the app checked for new data every second while the Arduino sent a reading only about every 2 seconds, so the app often read incomplete data. **The final V1 sketches don't send any Bluetooth data, so the app won't show readings with them.** I've kept it here as part of the project's history.

### Known limitations
- Step beeps fire only inside 1 °C windows, so a fast temperature rise can skip one.
- The ≥ 98 °C alarm can't be silenced.
- It measures temperature only; it doesn't detect froth directly.

---

## Version 2 — WatchOutMilk (2026) — In progress

A redesign around the **Seeed XIAO ESP32-C3**, with built-in WiFi replacing Bluetooth.

- **Done:** Stage 1 schematic in KiCad 10 (XIAO ESP32-C3, MAX6675 HW-550 breakout, SSD1306 OLED, passive buzzer, RGB status LED).
- **In progress:** 2-layer PCB layout for LionCircuits.
- **Planned:** 3D-printed enclosure (Fusion 360), firmware, and later WiFi alerts to a phone.

---

## License
MIT. See [LICENSE](LICENSE).

**Author:** Shamanthak Reddy Mallu · [Portfolio](https://shamanthak-reddy-mallu.vercel.app/) · [LinkedIn](https://linkedin.com/in/shamanthak)
