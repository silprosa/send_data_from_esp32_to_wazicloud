 ESP32 DHT11 Sensor Data to WaziCloud

This project demonstrates how to read temperature and humidity data from a DHT11 sensor using an ESP32 microcontroller and send the data to WaziCloud.
I used the  developed this project using PlatformIO in VSCode to efficiently manage dependencies, build, and upload the code to my ESP32 microcontroller.

The project includes the following components:
- ESP32 microcontroller: Used for reading sensor data and connecting to WiFi.
- **DHT11 sensor**: Measures temperature and humidity
- **WaziCloud**:platform where the sensor data is sent and stored.

The code reads temperature and humidity from the DHT11 sensor, connects to WiFi, and sends the data to WaziCloud at regular intervals.

Components

- ESP32 Development Board
- DHT11 Temperature and Humidity Sensor
- Jumper Wires
- Breadboard
 Wiring

| DHT11 Pin | ESP32 Pin |
|-----------|-----------|
| VCC       | 3.3V      |
| GND       | GND       |
| Data      | GPIO 27   |

Setup
 Prerequisites

- **PlatformIO Core (CLI) or PlatformIO IDE for VSCode**
  - Install PlatformIO by following the instructions [here](https://platformio.org/install).
 Installing Libraries

This project requires the following libraries:
- **DHT sensor library**
- **Adafruit Unified Sensor library**

You can add these libraries to your `platformio.ini` file: (IF NOT ALREADY PRESENT)

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed =   ; Serial monitor baud rate

upload_port = 115200 

    
