# STM32 RTC with UART Output Project
This project demonstrates how to configure the STM32 Real-Time Clock (RTC) and output the current date and time over UART to a serial terminal like PuTTY

## Project Overview
**Microcontroller**: STM32

**Peripherals used**:

- **RTC (Real-Time Clock)** — for time and date keeping

- **USART2 (UART)** — for serial communication to a PC

**Goal**: Print the current time and date over UART every second.

## Configuration Steps (in STM32CubeMX)
Follow these steps before generating the code:

1. **Clear All Existing Pinouts**
   - Open the .ioc file in STM32CubeIDE or STM32CubeMX.
   - Click on Pinout view.
   - Clear all pre-configured pins to start with a clean setup.

2. **Enable and Configure the RTC**
   - Go to the Timers section.
   - Select RTC.
   - Enable **Activate Clock Source**
   - Enable **Activate Calendar**.
   - Set the current date and time in the configuration panel.

3. **Enable USART2 (UART)**
   - Go to the Connectivity section.
   - Select USART2 and configure it as **Asynchronous**.
   - Set the desired **Baud Rate** (115200).
   - Configure **TX** and **RX** pins (typically **PA2** and **PA3** for USART2 on many STM32 boards).

4. **Generate the Code**
   - Click on **Project > Generate Code**.