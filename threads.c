#include "main.h"

int	eating(t_vars *vars) {
	mutex(vars, pthread_mutex_lock);
	if (!checker(vars))
			return (0);
	print("has taken a fork", vars);
	if (!checker(vars))
			return (0);
	print("is eating", vars);
	usleep(vars->time_2_eat * 1000);
	gettimeofday(&vars->update_time_2_die, NULL);
	mutex(vars, pthread_mutex_unlock);
	return 0;
}

void	*philosopher(void *arg) {
	t_vars *vars = (t_vars *)arg;
	int i = 0;
	gettimeofday(&vars->update_time_2_die, NULL);
	print("is thinking", vars);
	while (!vars->notepme || i < vars->notepme)
	{
		eating(vars);
		if (!checker(vars))
			return (0);
		print("is sleeping", vars);
		if (!checker(vars))
			return (0);
		usleep(vars->time_2_sleep * 1000);
		if (!checker(vars))
			return (0);
		print("is thinking", vars);
		i++;
	}
	return 0;
}


// ==================================================================================================================================

// void	life_cycle()
// {

// }

// void	pt_oncreate(pthread_t *thread, void *data)
// {
// 	pthread_create(thread, NULL, life_cycle, data);
// }