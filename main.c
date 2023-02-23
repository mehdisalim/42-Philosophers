#include "main.h"


struct timeval current_time;

void	my_usleep(size_t n)
{
	struct timeval current_time2;
	size_t ms, s;
	gettimeofday(&current_time2, NULL);
	ms = n + current_time2.tv_usec;
	s = (n / 1000) + current_time2.tv_sec;
	while (1)
	{
		gettimeofday(&current_time2, NULL);
		if (current_time2.tv_sec >= s && current_time2.tv_usec >= ms)
			break;
	}
}

long	ft_atoi(const char *str)
{
	int				i;
	long			result;
	int				sign;

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

void	*philosopher(void *arg)
{
	t_vars *vars = (t_vars *)arg;
	pthread_mutex_lock(&vars->forks[vars->id]);
	pthread_mutex_lock(&vars->forks[(vars->id + 1) % 5]);
	printf("philo = %d\n", vars->philosophers[vars->id]);
	// my_usleep(vars->time_2_eat);
	pthread_mutex_unlock(&vars->forks[(vars->id + 1) % 5]);
	pthread_mutex_unlock(&vars->forks[vars->id]);
	return 0;
}

int main(int ac, char **av)
{
	if (5 != ac)
		return 0;

	t_vars vars;
	vars.number_of_philos = ft_atoi(av[1]);
	vars.time_2_eat = ft_atoi(av[2]);
	vars.time_2_die = ft_atoi(av[3]);
	vars.time_2_sleep = ft_atoi(av[4]);
	vars.philosophers = malloc((vars.number_of_philos + 1) * sizeof(int));
	vars.philosophers[vars.number_of_philos + 1] = 0;
	vars.forks = malloc((vars.number_of_philos + 1) * sizeof(pthread_mutex_t));
	int i = -1;
	while (++i < vars.number_of_philos)
		vars.philosophers[i] = i + 1;
	i = -1;
	while (++i <= vars.number_of_philos)
		pthread_mutex_init(&vars.forks[i], NULL);
	pthread_t *threads = malloc((vars.number_of_philos + 1) * sizeof(pthread_t));
	threads[vars.number_of_philos + 1] = 0;
	i = -1;
	while (++i < vars.number_of_philos)
	{
		vars.id = i;
		pthread_create(&threads[i], NULL, philosopher, &vars);
	}

	return (0);
}
