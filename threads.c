#include "main.h"

void	*philosopher(void *arg) {
	t_vars *vars = (t_vars *)arg;
	pthread_mutex_lock(vars->mutex_lock);
	gettimeofday(&vars->update_time_2_die, NULL);
	if (vars->philosopher % 2 == 0)
		my_usleep(100);
	int number_of_meals = vars->notepme * vars->number_of_philos;
	thinking(vars);
	while (eating(vars) && sleeping(vars) && (!number_of_meals || vars->eater[0] <= number_of_meals) && thinking(vars));
	pthread_mutex_destroy(vars->mutex_eat);
	mutex(vars, pthread_mutex_unlock);
	pthread_mutex_unlock(vars->exit_fork);
	pthread_mutex_destroy(vars->exit_fork);
	return (0);
}

void	*unlocker(void *args)
{
	t_vars *vars = (t_vars *)args;
	pthread_mutex_unlock(vars->mutex_lock);
	return (0);
}