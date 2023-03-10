#include "main.h"

int	print(char *str, t_vars *vars){
	if (pthread_mutex_lock(&vars->exit_fork[0]) == -1)
		return -1;
	printf("%ld %d %s\n", get_current_time(vars->start_time), vars->philosopher, str);
	if (pthread_mutex_unlock(&vars->exit_fork[0]) == -1)
		return -1;
	return (0);
}

int mutex(t_vars *vars, int (*func)(pthread_mutex_t*)) {
	if (func(&vars->fork))
		return (-1);
	if (vars->philosopher >= vars->number_of_philos && func(&(vars - vars->philosopher + 1)->fork))
		return (-1);
	else if (func(&(vars + 1)->fork))
		return (-1);
	else
		return (0);
}


int checker(t_vars *vars) {
	t_vars *var = vars - vars->philosopher + 1;
	int i = 0;
	int max = (var->notepme * var->number_of_philos) + (vars->number_of_philos / 4);
	int len = vars->number_of_philos;
	if (vars->notepme == 0)
		return (1);
	while (i < len)
	{
		if (var[i].eater[0] >= max)
			return (0);
		i++;
	}
	return (1);
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
