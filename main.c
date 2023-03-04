#include "main.h"

long	ft_atoi(const char *str)
{
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

long	get_current_time(struct timeval start_time)
{
	long	time;
	struct timeval end_time;
	gettimeofday(&end_time, NULL);
	time = (end_time.tv_sec - start_time.tv_sec) * 1000;
	time += (end_time.tv_usec - start_time.tv_usec) / 1000;
	return (time);
}

int	eating(t_vars *vars)
{
	if (vars->philosopher >= vars->number_of_philos)
	{
		pthread_mutex_lock(&vars->fork);
		pthread_mutex_lock(&(vars - vars->philosopher + 1)->fork);
	}
	else
	{
		pthread_mutex_lock(&vars->fork);
		pthread_mutex_lock(&(vars + 1)->fork);
	}
	if (get_current_time(vars->update_time_2_die) > vars->time_2_die)
	{
		vars->is_died[0] = 1;
		// return (0);
	}
	printf("%ld %d has taken a fork\n", get_current_time(vars->start_time), vars->philosopher);
	printf("%ld %d is eating\n", get_current_time(vars->start_time), vars->philosopher);
	usleep(vars->time_2_eat * 1000);
	vars->eater++;
	if (vars->philosopher >= vars->number_of_philos)
	{
		pthread_mutex_unlock(&vars->fork);
		pthread_mutex_unlock(&(vars - vars->philosopher + 1)->fork);
	}
	else
	{
		pthread_mutex_unlock(&vars->fork);
		pthread_mutex_unlock(&(vars + 1)->fork);
	}
	return (1);
}

int checker(t_vars *vars)
{
	t_vars *var = vars - vars->philosopher + 1;
	int i = 0;
	while (var[i].philosopher)
	{
		if (var[i].eater < var[i].notepme || var[i].is_died[0])
			return (0);
		i++;
	}
	return (1);
}

void	*philosopher(void *arg)
{
	t_vars *vars = (t_vars *)arg;
	int i = 0;
	while (!vars->notepme || i < vars->notepme)
	{
		gettimeofday(&vars->update_time_2_die, NULL);
		if (checker(vars) || vars->is_died[0])
		{
			if (vars->is_died[0])
				printf("%ld %d died\n", get_current_time(vars->start_time), vars->philosopher);
			return (0);
		}
		printf("%ld %d is thinking\n", get_current_time(vars->start_time), vars->philosopher);
		if (checker(vars) || vars->is_died[0])
		{
			if (vars->is_died[0])
				printf("%ld %d died\n", get_current_time(vars->start_time), vars->philosopher);
			return (0);
		}
		// eating(vars);
		if (!eating(vars) || checker(vars) || vars->is_died[0])
		{
			if (vars->is_died[0])
				printf("%ld %d died\n", get_current_time(vars->start_time), vars->philosopher);
			return (0);
		}
		printf("%ld %d is sleeping\n", get_current_time(vars->start_time), vars->philosopher);
		if (checker(vars) || vars->is_died[0])
		{
			if (vars->is_died[0])
				printf("%ld %d died\n", get_current_time(vars->start_time), vars->philosopher);
			return (0);
		}
		usleep(vars->time_2_sleep * 1000);
		if (checker(vars) || vars->is_died[0])
		{
			if (vars->is_died[0])
				printf("%ld %d died\n", get_current_time(vars->start_time), vars->philosopher);
			return (0);
		}
		printf("%ld %d is thinking\n", get_current_time(vars->start_time), vars->philosopher);
		if (checker(vars) || vars->is_died[0])
		{
			if (vars->is_died[0])
				printf("%ld %d died\n", get_current_time(vars->start_time), vars->philosopher);
			return (0);
		}
		i++;
	}
	return 0;
}

int main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (0);
	int n = ft_atoi(av[1]);
	int die = ft_atoi(av[2]);
	int eat = ft_atoi(av[3]);
	int sleep = ft_atoi(av[4]);
	int notepme = ft_atoi(av[5]);
	t_vars *vars = malloc((n + 1) * sizeof(t_vars));
	int died = 0;
	int i = -1;
	while (++i < n)
	{
		vars[i].number_of_philos = n;
		vars[i].time_2_eat = eat;
		vars[i].time_2_die = die;
		vars[i].time_2_sleep = sleep;
		vars[i].eater = 0;
		vars[i].is_died = &died;
		vars[i].notepme = notepme;
		vars[i].philosopher = i + 1;
		pthread_mutex_init(&vars[i].fork, NULL);
	}

	pthread_t *threads = malloc((n + 1) * sizeof(pthread_t));
	i = -1;
	while (++i < n)
	{
		gettimeofday(&vars[i].start_time, NULL);
		pthread_create(&threads[i], NULL, philosopher, &vars[i]);
		usleep(10);
	}
	i = -1;
	while (++i < n)
		pthread_join(threads[i], NULL);
	return (0);
}
