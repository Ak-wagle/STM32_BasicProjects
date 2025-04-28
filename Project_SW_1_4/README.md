# Push Button Switch Project

## Overview

This project involves interfacing **4 push buttons** with an STM32 microcontroller. The buttons are connected to the following GPIO pins:

- **SW1**: Pin `PB8`
- **SW2**: Pin `PC6`
- **SW3**: Pin `PB9`
- **SW4**: Pin `PC5`

The project reads the state of each push button and transmits the corresponding switch number to the serial monitor (using UART). Whenever you press any of the buttons, the corresponding number (SW1, SW2, SW3, or SW4) will be displayed in the serial monitor (like **Putty**).

## Hardware Requirements

1. **STM32 microcontroller** (STM32F401)
2. **4 Push Button Switches**
3. **Resistors** (usually 10kΩ for pull-up or pull-down configuration)
4. **Wires and Breadboard**
5. **Serial Communication Terminal** (Putty)

## Connections

- **SW1** is connected to **Pin PB8**
- **SW2** is connected to **Pin PC6**
- **SW3** is connected to **Pin PB9**
- **SW4** is connected to **Pin PC5**

Each switch will be configured as an **input pin** with a **pull-up or pull-down resistor or no-pull up/down (in our case)**

## Software Requirements

- **STM32CubeIDE** (for code writing, compiling, and flashing)
- **STM32CubeMX** (to configure the peripherals like GPIO and USART)
- **Serial Terminal Software** (Putty)
## Steps to Set Up the Project

### 1. Hardware Connections

Connect the push buttons to the STM32 microcontroller as follows:

- **SW1** to **Pin PB8**
- **SW2** to **Pin PC6**
- **SW3** to **Pin PB9**
- **SW4** to **Pin PC5**

Ensure that each button has a pull-up or pull-down resistor (10kΩ recommended) to ensure stable logic levels. The configuration can be done using STM32CubeMX.

### 2. STM32CubeMX Configuration

- Open **STM32CubeMX** and create a new project for your STM32 microcontroller.
- **Configure the GPIO pins**:
  - Set **PB8, PC6, PB9, PC5** as **GPIO input**.
  - Configure each pin with a **pull-up or pull-down resistor or no pull up/down** (depending on the wiring configuration).
- **Configure USART** for serial communication to transmit the button press information to a serial terminal (Putty).
- Generate the initialization code for **STM32CubeIDE**.

### 3. Write the Code in STM32CubeIDE

- Open the generated project in **STM32CubeIDE**.
- Implement the button state checking logic:
  - Read the state of each button using `HAL_GPIO_ReadPin()`.
  - If a button is pressed (logic High in our case), send the corresponding message to the serial monitor via USART.
  