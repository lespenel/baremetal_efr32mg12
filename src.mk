SRC := main.c \
	   \
	   drivers/clock_driver.c \
	   drivers/dcdc_driver.c \
	   drivers/gpio_driver.c \
	   drivers/timer_driver.c \
	   drivers/uart_driver.c \
	   \
	   platform/startup.c \
	   platform/nvic.c \
	   \
	   io/uart_io.c \
	   \
	   bsp/leds.c \
	   \
	   irq/timer_irq.c \
	   irq/uart_irq.c \
	   \
	   utils/bm_itoa.c \
	   utils/bm_regtoa.c \
	   utils/bm_strlen.c \
	   utils/bm_strchr.c \
	   utils/memset.c \
	   utils/memcpy.c \
	   \
	   scheduler/scheduler.c
