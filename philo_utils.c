#include "main.h"

int	print(char *str, t_vars *vars){
	if (pthread_mutex_lock(vars->exit_fork) == -1)
		return -1;
	if (vars->eater[0] != -1)
		printf("%ld %d %s\n", get_current_time((vars->start_time)[0]), vars->philosopher, str);
	if (pthread_mutex_unlock(vars->exit_fork) == -1)
		return -1;
	return (0);
}

int	print_die(t_vars *vars) {
	if (pthread_mutex_lock(vars->exit_fork) == -1)
		return -1;
	if (vars->eater[0] == -1)
	{
		pthread_mutex_unlock(vars->exit_fork);
		return (-1);
	}
	pthread_mutex_lock(vars->mutex_eat);
	printf("%ld %d died\n", get_current_time((vars->start_time)[0]), vars->philosopher);
	vars->eater[0] = -1;
	pthread_mutex_unlock(vars->mutex_eat);
	my_usleep(500);
	if (pthread_mutex_unlock(vars->exit_fork) == -1)
		return -1;
	return (0);
}

int mutex(t_vars *vars, int (*func)(pthread_mutex_t*), int show) {
	if (func(&vars->fork) )
		return (-1);
	if (show)
		print("has taken a fork", vars);
	if (vars->philosopher == vars->number_of_philos && func(&(vars - vars->philosopher + 1)->fork))
		return (-1);
	else if (func(&(vars + 1)->fork))
		return (-1);
	if (show)
		print("has taken a fork", vars);
	return (0);
}

int mutex_destroy(t_vars *vars, int (*func)(pthread_mutex_t*)) {
	if (func(&vars->fork))
		return (-1);
	if (vars->philosopher >= vars->number_of_philos && func(&(vars - vars->philosopher + 1)->fork))
		return (-1);
	else if (func(&(vars + 1)->fork))
		return (-1);
	else
		return (0);
}

