#ifndef LEDS_H
# define LEDS_H

#include <stdint.h>

void	leds_init(void);
void	leds_set(uint8_t led0, uint8_t led1);
void	led0_toggle(void);
void	led1_toggle(void);

#endif
