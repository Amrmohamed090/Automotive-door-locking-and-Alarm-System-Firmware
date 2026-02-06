# Automotive Door Locking and Alarm System Firmware

This repository contains the firmware for a simulated automotive door locking and lighting controller. The application is built around a cooperative state machine that responds to handle and door lock inputs, drives three indicator LEDs, and enforces an anti-theft timeout routine using STM32F4 peripherals.

## Features

- **Interrupt-driven inputs:** External interrupts on GPIOA0 and GPIOB1 capture handle and door lock button presses so state transitions occur immediately without polling.
- **Stateful lock management:** The main loop tracks door and handle states to prevent invalid transitions (e.g., locking the handle while the door is open) and sequences LED patterns to mirror each action.
- **Timer-backed lighting effects:** A single general-purpose timer (TIM2) provides elapsed time for hazard flashing, ambient lighting duration, and anti-theft delays, simplifying timing logic across the application.

## Repository Layout

```
.
├── Drivers/
│   ├── src/           # Application entry point and state machine logic (main.c)
│   ├── EXTI/          # External interrupt driver
│   ├── Gpio/          # GPIO abstraction driver
│   ├── GPT/           # General-purpose timer driver
│   ├── I2c/           # I2C communication driver
│   ├── Lib/           # Common utilities and type definitions
│   ├── Rcc/           # Reset and Clock Control driver
│   ├── Spi/           # SPI communication driver
│   ├── Uart/          # UART communication driver
│   ├── system/        # CMSIS startup code and vendor support files
│   ├── ldscripts/     # Linker scripts for STM32F4
│   └── Release/       # Build output (Makefiles, ELF, HEX files)
├── simulation/        # Proteus project archive for hardware simulation
└── README.md
```

## Target Hardware

- **MCU:** STM32F401xE (ARM Cortex-M4)
- **GPIO Inputs:** GPIOA0 (Handle button), GPIOB1 (Door lock button)
- **GPIO Outputs:** GPIOD0 (Lock LED), GPIOD1 (Hazard LED), GPIOD2 (Ambient LED)

## Getting Started

### Prerequisites

- GNU Arm Embedded Toolchain (`arm-none-eabi-gcc`, `arm-none-eabi-g++`, `arm-none-eabi-objcopy`, `arm-none-eabi-size`)
- Make (GNU Make 4.x or compatible)
- Optional: Proteus 8 or compatible simulator to open the project file in `simulation/`

### Building the Firmware

1. Ensure the GNU Arm toolchain is on your `PATH`.
2. From the repository root, invoke the release build:

   ```bash
   make -C Drivers/Release
   ```

   This produces the ELF and Intel HEX images in `Drivers/Release/`.

3. Flash the generated HEX file to the target MCU or load it into your preferred simulator/emulator.

### Cleaning Build Artifacts

To remove generated objects and binaries:

```bash
make -C Drivers/Release clean
```

## Runtime Behavior

| Action | Description |
|--------|-------------|
| **Handle Opening** | Unlocks the handle, turns on all LEDs immediately, keeps hazard LED lit for 0.5s, ambient LED for 2s, and starts a 10-second anti-theft timer. |
| **Handle Closing** | If the door is closed, locks the handle, turns lock LED off, and flashes hazard LED twice before returning to idle. |
| **Door Opening** | Only honored when the handle is unlocked. Turns on ambient LED. |
| **Door Closing** | Locks the door and powers down LEDs after a 1-second delay. |
| **Anti-theft** | If no button is pressed within 10 seconds after handle opening, the system auto-locks and flashes the hazard LED pattern. |

## Simulation

The `simulation/ARM Project.pdsprj.BEBO.abram.zip` archive contains the Proteus design used to demonstrate the firmware. Extract and open the project in Proteus to visualize the LED indicators and button inputs without hardware.

## License

This project is provided for educational purposes.
