#include "main.h"

void	*philosopher(void *arg) {
	t_vars *vars = (t_vars *)arg;
	int i = vars->notepme;
	gettimeofday(&vars->update_time_2_die, NULL);
	thinking(vars);
	while (i-- && eating(vars) && sleeping(vars) && thinking(vars));
	return (0);
}