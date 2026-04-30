#include "lib/ringbuf.h"

int		ringbuf_consume(t_ringbuf *buf, char *out)
{
	if (buf->len == 0)
		return (0);

	*out = buf->buffer[buf->tail];
	buf->tail = (buf->tail + 1) % RINGBUF_SIZE;
	--buf->len;

	return (1);
}

void	ringbuf_insert(t_ringbuf *buf, char in)
{
	buf->buffer[buf->head] = in;
	buf->head = (buf->head + 1) % RINGBUF_SIZE;

	if (buf->len < RINGBUF_SIZE)
		++buf->len;
	else
		buf->tail = (buf->tail + 1) % RINGBUF_SIZE;
}

void	ringbuf_init(t_ringbuf *buf)
{
	buf->head = 0;
	buf->tail = 0;
	buf->len = 0;
}
