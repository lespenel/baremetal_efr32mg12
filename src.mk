SRC := main.c \
	   \
	   debug_server/debug_server_init.c \
	   debug_server/debug_server_poll.c \
	   debug_server/debug_server_register_var.c \
	   debug_server/debug_server_exec_cmd.c \
	   debug_server/debug_server_inspect.c \
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
	   interfaces/transport.c \
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
