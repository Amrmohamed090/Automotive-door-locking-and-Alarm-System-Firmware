# Automotive door locking and Alarm System Firmware

This repository contains the firmware for a simulated automotive door locking and lighting controller. The application is built around a cooperative state machine that responds to handle and door lock inputs, drives three indicator LEDs, and enforces an anti-theft timeout routine using STM32F4 peripherals.

## Features

- **Interrupt-driven inputs:** External interrupts on GPIOA0 and GPIOB1 capture handle and door lock button presses so state transitions occur immediately without polling.【F:all_files/src/main.c】【F:all_files/EXTI/EXTI.c】
- **Stateful lock management:** The main loop tracks door and handle states to prevent invalid transitions (e.g., locking the handle while the door is open) and sequences LED patterns to mirror each action.【F:all_files/src/main.c】
- **Timer-backed lighting effects:** A single general-purpose timer (TIM2) provides elapsed time for hazard flashing, ambient lighting duration, and anti-theft delays, simplifying timing logic across the application.【F:all_files/GPT/Gpt.c】【F:all_files/src/main.c】

## Repository layout

- `all_files/src/`: Application entry point and state machine logic (`main.c`).
- `all_files/GPT/`, `all_files/EXTI/`, `all_files/Gpio/`, `all_files/Rcc/`: Peripheral drivers for the general-purpose timer, external interrupts, GPIO abstraction, and clock control.
- `all_files/system/` and `all_files/Lib/`: CMSIS startup code, linker scripts, and vendor support files for the STM32F4 toolchain.
- `all_files/Release/`: Generated Makefiles and build outputs produced by STM32CubeIDE/ GNU Arm Embedded toolchain.
- `simulation/`: Proteus project archive for hardware simulation.

## Getting started

### Prerequisites

- GNU Arm Embedded Toolchain (`arm-none-eabi-gcc`, `arm-none-eabi-g++`, `arm-none-eabi-objcopy`, `arm-none-eabi-size`).
- Make (GNU Make 4.x or compatible).
- Optional: Proteus or a compatible simulator to open the project file in `simulation/`.

### Building the firmware

1. Ensure the GNU Arm toolchain is on your `PATH`.
2. From the repository root, invoke the release build:

   ```bash
   make -C all_files/Release
   ```

   This produces the ELF (`Lab4_Startup_Project_TODO.elf`) and Intel HEX (`Lab4_Startup_Project_TODO.hex`) images in `all_files/Release/` along with associated size and listing files.【all_files/Release/makefile】

3. Flash the generated HEX file to the target MCU or load it into your preferred simulator/emulator.

### Cleaning build artifacts

To remove the generated objects and binaries, run:

```bash
make -C all_files/Release clean
```

## Runtime behavior

- **Handle opening:** Unlocks the handle, turns on all LEDs immediately, keeps the hazard LED lit for 0.5 seconds, the ambient LED for 2 seconds, and starts a 10-second anti-theft timer.【F:all_files/src/main.c】
- **Handle closing:** If the door is closed, locks the handle, turns the lock LED off, and flashes the hazard LED twice before returning to idle.【F:all_files/src/main.c】
- **Door opening/closing:** Door actions are only honored when their prerequisites are satisfied (e.g., the handle must be unlocked before opening). Closing the door powers down LEDs after a 1-second delay.【F:all_files/src/main.c】
- **Anti-theft:** Ten seconds after the handle is opened without further interaction, the system relocks the handle and plays the same hazard pattern as manual locking.【/src/main.c】

## Simulation and testing

The `simulation/ARM Project.pdsprj.BEBO.abram.zip` archive contains the Proteus design used to demonstrate the firmware. Extract and open the project in Proteus to visualize the LED indicators and button inputs without hardware.

