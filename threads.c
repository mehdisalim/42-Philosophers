#include "main.h"

void	*philosopher(void *arg) {
	t_vars *vars = (t_vars *)arg;
	gettimeofday(&vars->update_time_2_die, NULL);
	thinking(vars);
	while (eating(vars) && sleeping(vars) && (!vars->notepme || vars->eater[0] <= vars->notepme) && thinking(vars));
	mutex(vars, pthread_mutex_unlock, 0);
	pthread_mutex_unlock(vars->mutex_eat);
	pthread_mutex_unlock(vars->exit_fork);
	return (0);
}
