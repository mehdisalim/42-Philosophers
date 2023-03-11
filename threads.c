#include "main.h"

int	eating(t_vars *vars) {
	mutex(vars, pthread_mutex_lock);
	// if (!checker(vars))
	// 		return (0);
	print("has taken a fork", vars);
	// if (!checker(vars))
	// 		return (0);
	print("is eating", vars);
	usleep(vars->time_2_eat * 1000);
	pthread_mutex_lock(&vars->mutex_eat[0]);
	vars->eater[0]++;
	pthread_mutex_unlock(&vars->mutex_eat[0]);
	gettimeofday(&vars->update_time_2_die, NULL);
	mutex(vars, pthread_mutex_unlock);
	return 0;
}

void	*philosopher(void *arg) {
	t_vars *vars = (t_vars *)arg;
	int i = 0;
	gettimeofday(&vars->update_time_2_die, NULL);
	while (!vars->notepme || i < vars->notepme)
	{
		print("is thinking", vars);
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