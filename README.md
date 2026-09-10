# IOT-Based-Industrial-Device-Control-and-Automation-System

## 📌 Project Overview

This project is an **IOT-Based-Industrial-Device-Control-and-Automation-System** that allows an LED to be controlled remotely using **Arduino IoT Cloud**.

The system uses an **ESP8266 Wi-Fi module** as the IoT communication device and an **LPC2129 ARM7 microcontroller** as the hardware controller.

When the LED switch is changed in Arduino IoT Cloud, the ESP8266 receives the updated Boolean value through Wi-Fi. The ESP8266 converts the Boolean command into a UART character and sends it to the LPC2129.

The LPC2129 receives the character through **UART0** and controls LED1 through GPIO **P0.14**.

---

## 🚀 Project Architecture

```text
┌─────────────────────────┐
│   Arduino IoT Cloud     │
│                         │
│   LED1 = ON / OFF       │
└────────────┬────────────┘
             │
             │ Wi-Fi
             ▼
┌─────────────────────────┐
│        ESP8266          │
│                         │
│  Cloud Boolean Value    │
│          ↓              │
│  Convert to UART Cmd    │
│                         │
│  ON  → '1'              │
│  OFF → '5'              │
└────────────┬────────────┘
             │
             │ UART
             ▼
┌─────────────────────────┐
│        LPC2129          │
│                         │
│        UART0            │
│          ↓              │
│   Command Processing    │
│          ↓              │
│       GPIO P0.14        │
└────────────┬────────────┘
             │
             ▼
          ┌─────┐
          │ LED1│
          └─────┘
```

---

# 🎯 Objective

The objective of this project is to demonstrate how an IoT cloud platform can control a physical device using two different communication technologies:

```text
Cloud Communication → Wi-Fi
Local Communication → UART
Device Control      → GPIO
```

This project combines:

* IoT
* Wi-Fi communication
* Arduino IoT Cloud
* ESP8266
* UART communication
* ARM7 LPC2129
* GPIO control
* Embedded C

---

# 🔄 Complete Working

## 1. Arduino IoT Cloud

A Boolean variable such as:

```text
LED1
```

is created in Arduino IoT Cloud.

The user controls the LED using an ON/OFF switch.

### Cloud ON

```text
LED1 = TRUE
```

The ESP8266 receives the updated Boolean value through Wi-Fi.

---

## 2. ESP8266

The ESP8266 acts as the bridge between the **IoT Cloud** and the **LPC2129**.

It receives the cloud Boolean value and converts it into a UART command.

```text
Cloud Value       UART Character

TRUE       →      '1'
FALSE      →      '5'
```

Therefore:

```text
Arduino Cloud
      │
      │ TRUE
      ▼
   ESP8266
      │
      │ '1'
      ▼
   LPC2129
      │
      ▼
   LED1 ON
```

For OFF:

```text
Arduino Cloud
      │
      │ FALSE
      ▼
   ESP8266
      │
      │ '5'
      ▼
   LPC2129
      │
      ▼
   LED1 OFF
```

---

# 📡 UART Communication

The ESP8266 communicates with the LPC2129 using UART.

The LPC2129 uses **UART0**.

The UART initialization configures the UART pins and baud-rate registers.

The LPC2129 waits for incoming data:

```c
while((U0LSR & 1) == 0);

return U0RBR;
```

This means the microcontroller waits until a UART character is received and then reads it from the UART receive buffer.

---

# 💡 LED Control Logic

LED1 is connected to:

```text
LPC2129 P0.14
```

The code defines:

```c
#define LED1 1<<14
```

The LPC2129 receives a character from UART.

### If received character is `'1'`

```text
Received Data = '1'
        ↓
LED1 ON
        ↓
P0.14 controlled
        ↓
LCD displays LED 1 ON
```

### If received character is `'5'`

```text
Received Data = '5'
        ↓
LED1 OFF
        ↓
P0.14 controlled
        ↓
LCD displays LED 1 OFF
```

This command processing is implemented in the LPC2129 application.

---

# 🖥️ LCD Display

A 16x2 LCD is connected to the LPC2129.

The project displays:

```text
LED CONTROLLER
```

during startup.

When LED1 is controlled, the LCD displays the corresponding status:

```text
LED 1 ON.....
```

or:

```text
LED 1 OFF.....
```

The LCD driver uses P0.4–P0.11 for data, P0.12 for RS and P0.13 for Enable according to the uploaded LCD definitions.

---

# 🔢 Command Mapping

| Arduino Cloud | ESP8266 UART | LPC2129 Action | LED1 |
| ------------- | ------------ | -------------- | ---- |
| ON / TRUE     | `'1'`        | Turn ON        | ON   |
| OFF / FALSE   | `'5'`        | Turn OFF       | OFF  |

---

# 🔌 Hardware Connections

## ESP8266 ↔ LPC2129 UART

```text
ESP8266                 LPC2129

TX  ------------------> RX
RX  <------------------ TX
GND ------------------- GND
```

### Important

UART communication requires:

```text
TX → RX
RX → TX
GND → GND
```

The two devices must also use compatible **logic voltage levels**.

---

# 💡 LPC2129 LED Connection

```text
LPC2129 P0.14
     │
     │
   Resistor
     │
     │
    LED1
     │
    GND
```

LED1 is controlled through GPIO P0.14.

---

# 📺 LPC2129 LCD Connection

According to the current LCD driver:

```text
LCD Data D0-D7 → P0.4-P0.11
LCD RS         → P0.12
LCD E          → P0.13
```

The LCD driver configures these pins as outputs.

---

# 🧰 Hardware Requirements

| Component                      |    Quantity |
| ------------------------------ | ----------: |
| LPC2129 ARM7 Development Board |           1 |
| ESP8266                        |           1 |
| 16x2 LCD                       |           1 |
| LED                            |           1 |
| Current limiting resistor      |           1 |
| USB/UART interface             |           1 |
| Jumper wires                   | As required |
| Power supply                   |           1 |

---

# 💻 Software Requirements

* Arduino IoT Cloud
* Arduino IDE
* ESP8266 Board Package
* Keil µVision
* LPC2129 ARM7 toolchain
* Proteus *(optional)*
* Serial Terminal *(optional)*

---

# 📂 Project Structure

```text
IoT-LPC2129-LED-Control/
│
├── ESP8266/
│   ├── ESP8266_LED_Control.ino
│   └── thingProperties.h
│
├── LPC2129/
│   ├── led.c
│   ├── uart.c
│   ├── UART.h
│   └── lcd_display.h
│
└── README.md
```

---

# 🧠 Technologies Used

### Arduino IoT Cloud

Used for:

* Remote device control
* Boolean ON/OFF switch
* Cloud-to-device communication

### ESP8266

Used as:

* Wi-Fi device
* Arduino IoT Cloud client
* UART command transmitter

### UART

Used as the communication link between:

```text
ESP8266 ↔ LPC2129
```

### LPC2129

Used as the main embedded controller for:

* UART reception
* Command processing
* GPIO control
* LCD status display

### GPIO

Used to control LED1 through:

```text
P0.14
```

---

# 🔬 Example Working Scenario

Suppose the user is away from the hardware.

The user opens Arduino IoT Cloud and changes:

```text
LED1 = ON
```

The process is:

```text
Arduino IoT Cloud
       ↓
      Wi-Fi
       ↓
    ESP8266
       ↓
 UART Character '1'
       ↓
    LPC2129
       ↓
    UART0 RX
       ↓
  Command = '1'
       ↓
    GPIO P0.14
       ↓
     LED1 ON
```

The LCD shows:

```text
LED CONTROLLER
LED 1 ON.....
```

When the cloud switch is changed to OFF:

```text
Arduino IoT Cloud
       ↓
      Wi-Fi
       ↓
    ESP8266
       ↓
 UART Character '5'
       ↓
    LPC2129
       ↓
    UART0 RX
       ↓
  Command = '5'
       ↓
    GPIO P0.14
       ↓
    LED1 OFF
```

---

# ⭐ Key Features

* 🌐 Remote LED control through Internet
* ☁️ Arduino IoT Cloud integration
* 📶 ESP8266 Wi-Fi communication
* 🔌 UART communication
* ⚡ LPC2129 ARM7 microcontroller
* 💡 GPIO-based LED control
* 📺 LCD status indication
* 🔄 Cloud Boolean → UART character conversion
* 🧑‍💻 Embedded C implementation

---

# 📈 Future Enhancements

The project can be expanded to control multiple devices.

For example:

```text
Arduino Cloud
     │
     ├── LED1
     ├── LED2
     ├── LED3
     └── LED4
          │
          ▼
       ESP8266
          │
          ▼
        UART
          │
          ▼
       LPC2129
          │
     ┌────┼────┬────┐
     ▼    ▼    ▼    ▼
    LED1 LED2 LED3 LED4
```

Possible future features:

* Control 4 or 8 LEDs
* Relay control
* Home automation
* Sensor monitoring
* Temperature monitoring
* Multiple cloud variables
* UART acknowledgement
* Device status feedback to cloud
* Mobile IoT control
* FreeRTOS-based implementation

---

# 🎓 Skills Demonstrated

This project demonstrates practical knowledge of:

```text
Arduino IoT Cloud
       ↓
Wi-Fi Communication
       ↓
ESP8266 Programming
       ↓
UART Protocol
       ↓
ARM7 LPC2129
       ↓
Embedded C
       ↓
GPIO Register Programming
       ↓
LCD Interfacing
```

---

# 👨‍💻 Author

**Gowtham**

Embedded Systems | Embedded C | ARM7 | LPC2129 | IoT

---

# 📜 License

This project is created for **educational and learning purposes**.
