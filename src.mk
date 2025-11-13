SRC := startup.c \
	   main.c \
	   \
	   drivers/clock_driver.c \
	   drivers/dcdc_driver.c \
	   drivers/gpio_driver.c \
	   drivers/uart_driver.c \
	   \
	   io/uart_io.c \
	   io/led_io.c \
	   \
	   irq/timer_irq.c \
	   \
	   utils/bm_itoa.c \
	   utils/bm_regtoa.c \
	   utils/bm_strlen.c \
	   utils/memset.c \
	   \
	   scheduler/scheduler.c
