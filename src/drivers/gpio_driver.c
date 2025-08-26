#include "gpio.h"

/**
 * @brief Enable a GPIO Pin in the specfied Port and desired Mode
 *
 * @param port_id  ID of the PORT
 * @param pin_nb Index of the Pin
 * @param mode Pin Mode (e.g PusshPull, Input,..)
 */
void	enable_gpio_port(uint32_t port_id, uint32_t pin_nb, uint32_t mode)
{
	if (pin_nb < 8)
	{
		GPIO->P[port_id].MODEL &= ~(0xF << (pin_nb * 4));
		GPIO->P[port_id].MODEL |= (mode << (pin_nb * 4));
	}
	else
	{
		GPIO->P[port_id].MODEH &= ~(0xF << ((pin_nb - 8) * 4));
		GPIO->P[port_id].MODEH |= (mode << ((pin_nb - 8) * 4));
	}
}
