# UART Confgiuration

## Context

The microcontroller provides multiple USART peripherals (USART0…USART3).  
By default, UART pins are not routed and peripherals are disabled.  
For serial communication, we configure a USART in asynchronous mode with:  

- 8 data bits  
- 1 stop bit  
- No parity  

We also optionally enable a virtual COM port (VCOM) for debugging over a dedicated GPIO.  

## Changes Applied

- Enabled the clock for the selected USART peripheral.  
- Configured GPIO pins for TX and RX:  
- TX → push-pull output  
- RX → input  
- Set the USART to asynchronous mode and disabled loopback.  
- Configurable frame format: 8-bit data, 1 stop bit, no parity.  
- Configured TX/RX pin locations via ROUTELOC0 and enabled TX output via ROUTEPEN.  
- Enabled TX command to start transmission.  
- Optionally enabled VCOM via GPIO pin (PA5).  

## Reasoning

- Enabling the peripheral clock is mandatory before configuring registers.  
- TX must be push-pull to drive the line, RX must be input to read data.  
- Fractional clock divider ensures accurate baud rate for asynchronous communication.  
- VCOM is useful for debugging without requiring additional hardware  

## Notes

- Baud rate calc assumes 16x oversampling; changing oversampling requires updating CLKDIV.  
- TX is enabled by default, RX can be enabled similarly if needed.  
- Pin routing (ROUTELOC0) must match the board layout.  

## References

- USART_CTRL: controls sync mode and loopback.  
- USART_FRAME: configures data bits, stop bits, and parity.  
- USART_CLKDIV: fractional divider for baud rate.  
- RM p.500+: USART register map and asynchronous mode description.  
