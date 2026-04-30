SRC := main.c \
	   \
	   console/cli_exec.c \
	   console/console.c \
	   console/echo.c \
	   console/help.c \
	   console/inspect.c \
	   console/send.c \
	   \
	   drivers/clock_driver.c \
	   drivers/dcdc_driver.c \
	   drivers/gpio_driver.c \
	   drivers/timer_driver.c \
	   drivers/usart_driver.c \
	   \
	   platform/startup.c \
	   platform/nvic.c \
	   \
	   bsp/board_init.c \
	   bsp/leds.c \
	   bsp/serial_usart.c \
	   \
	   irq/timer_irq.c \
	   irq/usart_irq.c \
	   \
	   interfaces/serial.c \
	   \
	   lib/ringbuf.c \
	   \
	   utils/bm_itoa.c \
	   utils/bm_regtoa.c \
	   utils/bm_strlen.c \
	   utils/bm_strchr.c \
	   utils/bm_strcmp.c \
	   utils/bm_strtok_r.c \
	   utils/memset.c \
	   utils/memcpy.c \
	   \
	   scheduler/scheduler.c
