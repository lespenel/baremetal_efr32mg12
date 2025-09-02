#ifndef LED_IO_H
# define LED_IO_H

#include <stdint.h>

void	leds_init(void);
void	leds_set(uint8_t led0, uint8_t led1);

#endif
