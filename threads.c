#include "main.h"

void	*philosopher(void *arg) {
	t_vars *vars = (t_vars *)arg;
	int number_of_meals = vars->notepme * vars->number_of_philos;
	gettimeofday(&vars->update_time_2_die, NULL);
	thinking(vars);
	while (eating(vars) && sleeping(vars) && (!number_of_meals || vars->eater[0] <= number_of_meals) && thinking(vars));
	mutex(vars, pthread_mutex_unlock);
	pthread_mutex_unlock(vars->mutex_eat);
	pthread_mutex_unlock(vars->exit_fork);
	return (0);
}

void	*unlocker(void *args)
{
	t_vars *vars = (t_vars *)args;
	pthread_mutex_unlock(vars->mutex_lock);
	return (0);
}