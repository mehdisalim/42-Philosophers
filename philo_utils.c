#include "main.h"

int	print(char *str, t_vars *vars){
	if (pthread_mutex_lock(vars->exit_fork) == -1)
		return -1;
	// if (vars->eater[0] == -1)
	// {
	// 	pthread_mutex_unlock(vars->exit_fork);
	// 	return (1);
	// }
	printf("%ld %d %s\n", get_current_time(vars->start_time), vars->philosopher, str);
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
	printf("%ld %d died\n", get_current_time(vars->start_time), vars->philosopher);
	vars->eater[0] = -1;
	pthread_mutex_unlock(vars->mutex_eat);
	my_usleep(500);
	if (pthread_mutex_unlock(vars->exit_fork) == -1)
		return -1;
	return (0);
}

int mutex(t_vars *vars, int (*func)(pthread_mutex_t*)) {
	if (func(&vars->fork) )
		return (-1);
	if (vars->philosopher == vars->number_of_philos && func(&(vars - vars->philosopher + 1)->fork))
		return (-1);
	else if (func(&(vars + 1)->fork))
		return (-1);
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

long	ft_atoi(const char *str){
	int				i;
	long			result;
	int				sign;

	if (!str || !*str)
		return (0);
	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' )
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] <= '9' && str[i] >= '0')
	{
		result = (result * 10) + str[i] - 48;
		i++;
	}
	return (result * sign);
}
