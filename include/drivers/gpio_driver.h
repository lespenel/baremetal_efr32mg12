#ifndef GPIO_DRIVER_H
# define GPIO_DRIVER_H

#include <stdint.h>

// GPIO_Px_MODEH - Port Pin Mode (p.1125)
typedef enum
{
	// Input disabled. Pullup if DOUT is set
	gpio_mode_DISABLED					= 0x00000000UL,
	// Input enabled. Filter if DOUT is set
	gpio_mode_INPUT						= 0x00000001UL,
	// Input enabled. DOUT determines pull direction
	gpio_mode_INPUTPULL					= 0x00000002UL,
	// Input enabled with filter. DOUT determines pull direction
	gpio_mode_INPUTPULLFILTER			= 0x00000003UL,
	// Push-pull output
	gpio_mode_PUSHPULL					= 0x00000004UL,
	// Push-pull using alternate control
	gpio_mode_PUSHPULLALT				= 0x00000005UL,
	// Wired-or output
	gpio_mode_WIREDOR					= 0x00000006UL,
	// Wired-or output with pull-down
	gpio_mode_WIREDORPULLDOWN			= 0x00000007UL,
	// Open-drain output
	gpio_mode_WIREDAND					= 0x00000008UL,
	// Open-drain output with filter
	gpio_mode_WIREDANDFILTER			= 0x00000009UL,
	// Open-drain output with pullup
	gpio_mode_WIREDANDPULLUP			= 0x0000000AUL,
	// Open-drain output with filter and pullup
	gpio_mode_WIREDANDPULLUPFILTER		= 0x0000000BUL,
	// Open-drain output using alternate control
	gpio_mode_WIREDANDALT				= 0x0000000CUL,
	// Open-drain output using alternate control with filter
	gpio_mode_WIREDANDALTFILTER			= 0x0000000DUL,
	// Open-drain output using alternate control with pullup
	gpio_mode_WIREDANDALTPULLUP			= 0x0000000EUL,
	// Open-drain output using alternate control with filter and pullup
	gpio_mode_WIREDANDALTPULLUPFILTER	= 0x0000000FUL,

}	GPIO_MODE_TypeDef;

void	enable_gpio_port(uint32_t port_id, uint32_t pin_nb, uint32_t mode);

#endif
