#include "main.h"

void	*philosopher(void *arg) {
	t_vars *vars = (t_vars *)arg;
	pthread_mutex_lock(vars->mutex_lock);
	if (vars->philosopher % 2 == 0)
		usleep(50);
	gettimeofday(&vars->start_time, NULL);
	gettimeofday(&vars->update_time_2_die, NULL);
	int number_of_meals = vars->notepme * vars->number_of_philos;
	thinking(vars);
	while (eating(vars) && sleeping(vars) && vars->eater[0] <= number_of_meals && thinking(vars));
	pthread_mutex_destroy(vars->mutex_eat);
	mutex(vars, pthread_mutex_unlock);
	return (0);
}

void	*unlocker(void *args)
{
	pthread_mutex_t *mutex_lock = (pthread_mutex_t *)args;
	pthread_mutex_unlock(mutex_lock);
	return (0);
}