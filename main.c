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

long	get_current_time(t_vars *vars)
{
	long	time;
	gettimeofday(&vars->end_time, NULL);
	time = (vars->end_time.tv_sec - vars->start_time.tv_sec) * 1000;
	time += (vars->end_time.tv_usec - vars->start_time.tv_usec) / 1000;
	return (time);
}

void	sleeping(t_vars *vars)
{
	printf("%ld %d is sleeping\n", get_current_time(vars), vars->philosopher);
	usleep(vars->time_2_sleep * 1000);
}

void	eating(t_vars *vars)
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
	printf("%ld %d has taken a fork\n", get_current_time(vars), vars->philosopher);
	printf("%ld %d is eating\n", get_current_time(vars), vars->philosopher);
	usleep(vars->time_2_eat * 1000);
	vars->eater[0] += 1;
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
}

void	*philosopher(void *arg)
{
	t_vars *vars = (t_vars *)arg;
	int i = 0;
	while (!vars->notepme || i < vars->notepme)
	{
		
		printf("%ld %d is thinking\n", get_current_time(vars), vars->philosopher);
		eating(vars);
		sleeping(vars);
		printf("%ld %d is thinking\n", get_current_time(vars), vars->philosopher);
		i++;
	}
	return 0;
}

int main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (0);
	int n = ft_atoi(av[1]);
	int eat = ft_atoi(av[3]);
	int die = ft_atoi(av[2]);
	int sleep = ft_atoi(av[4]);
	int notepme = ft_atoi(av[5]);
	t_vars *vars = malloc((n + 1) * sizeof(t_vars));
	int eat_index = 0;
	int i = -1;
	while (++i < n)
	{
		vars[i].number_of_philos = n;
		vars[i].time_2_eat = eat;
		vars[i].time_2_die = die;
		vars[i].time_2_sleep = sleep;
		vars[i].eater = &eat_index;
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
