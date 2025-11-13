#ifndef SCHEDULER_H
# define SCHEDULER_H

#include <stdint.h>

typedef struct s_task
{
	void		(*callback)(void);
	uint32_t	interval;
	uint32_t	last_run;

}	t_task;

void	scheduler_run(void);

#endif
