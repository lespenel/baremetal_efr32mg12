# Clock Configuration (RM p.355)

## Context
The microcontroller supports multiple oscillators.  
By default, the internal RC oscillators (HFRCO, LFRCO) are used at startup.  
For higher precision and stability, we switch to external crystal oscillators:  
- `HFXO` (High-Frequency Crystal Oscillator) → used as system clock (HFCLK)  
- `LFXO` (Low-Frequency Crystal Oscillator) → used as reference for calibration and  
    low-power timers

## Changes Applied
- Enabled `HFXO` and waited for stabilization.  

- Enabled `LFXO` and waited for stabilization.  

- Switched HFCLK source from internal RC oscillator to `HFXO`.  

- Enabled peripheral clocks (GPIO, TIMER0).  

## Reasoning
- Internal RC oscillators are fast to start but inaccurate (±1%).  

- External crystal oscillators provide stable and accurate clocking for CPU and  
    peripherals.  

## Notes
- Order matters:  
    1. Power setup (DCDCInit) must be done before enabling `HFXO`.  

- Switching HFCLK to `HFXO` should only be done once `HFXO` is stable.  

## References
- `HFXO`: external high-frequency oscillator, required for accurate HFCLK.  

- `LFXO`: external 32.768 kHz oscillator, used as calibration reference and RTC.  

- RM p.300+: Clock Management Unit (CMU) overview and oscillator control.  
