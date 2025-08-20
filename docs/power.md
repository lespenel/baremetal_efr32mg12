# Power Configuration (RM p.241)

## Context
The microcontroller uses an internal `LDO` regulator by default. To support high frequencies on the `HFXO`,
the `DCDC` must be switched as the main power source. (it is mandatory to configure the power source right from the start)

## Changes Applied
- Enabled `DCDC` as the main power supply (`DVDD`) instead of the default LDO.
- Set `DCDC` to **Low Noise** mode to enable it and ensure stability at high frequencies.

## Reasoning
- `LDO` insufficient for high-frequency `HFXO`.
- Low Noise mode reduces electrical noise affecting MCU stability.

## Notes
- Must be called **before** `HFXO` initialization.

## References
- `DCDC`:  switch-mode regulator providing higher efficiency at high current.
- `LDO`:  low-dropout linear regulator, simpler but limited current.
- Reference Manual  p.276: EMU_PWRCTRL - Power Control Register
