#ifndef RINGBUF_H
# define RINGBUF_H

#include <stdint.h>

#define RINGBUF_SIZE	1024

typedef struct s_ringbuf
{
	char		buffer[RINGBUF_SIZE];
	uint16_t	len;
	uint16_t	head;
	uint16_t	tail;
}	t_ringbuf;

int		ringbuf_consume(t_ringbuf *buf, char *out);
void	ringbuf_insert(t_ringbuf *buf, char in);
void	ringbuf_init(t_ringbuf *buf);

#endif
