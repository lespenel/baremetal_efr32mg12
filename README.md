# Baremetal for EFR32MG12P
## Architecture

- **Target**: EFR32MG12P (ARM® Cortex-M4)
- **Mode**: Bare-metal (no OS, no HAL)

## Overview

This project contains a bare-metal firmware written for the EFR32MG12P microcontroller.
It is designed to run without any operating system or hardware abstraction layer (HAL),
providing full control over the hardware.

Current features:
- Minimal startup code
- LED blinking via GPIO

## Build

You need `arm-none-eabi-gcc` and `make`

```bash
make       # build 'firmware.s37' in the bin/ directory
make elf   # build 'firmware.elf' only in the build/ directory
```

The final file to flash is `bin/firmware.s37`

## Hardware Used

- **Mainboard**: Wireless Pro Kit Mainboard – BRD4002A Rev A06
- **Radio Board**: EFR32MG12 2.4 GHz 19 dBm – BRD4161A Rev A02
- **MCU**: EFR32MG12P432F1024GL125

See `hardware.md` for more details.

### Resources

- [Reference Manual](https://www.silabs.com/documents/public/reference-manuals/efr32xg12-rm.pdf) – Reference manual for EFR32MG12P
- [Datasheet](https://www.silabs.com/documents/public/data-sheets/efr32mg12-datasheet.pdf) – Datasheet for EFR32MG12P
- [simplicity-commander-cli](https://docs.silabs.com/simplicity-commander/latest/simplicity-commander-commands/) – Commands to flash the firm on the board

### Credits
- [Léo Espenel](https://github.com/lespenel)

Feel free to suggest improvements!
