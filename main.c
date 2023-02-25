#include "main.h"

void	my_usleep(size_t n)
{
	struct timeval current_time2;
	struct timeval current_time;
	size_t ms, s;
	gettimeofday(&current_time2, NULL);
	gettimeofday(&current_time, NULL);
	s = (n / 1000) + current_time2.tv_sec;
	ms = (n % 1000) + (current_time2.tv_usec / 1000);
	while (1)
	{
		gettimeofday(&current_time2, NULL);
		if (current_time2.tv_sec >= s && (current_time2.tv_usec / 1000) == ms)
			break ;
		else if (current_time2.tv_sec > s && ((current_time.tv_usec - current_time2.tv_usec) / 1000) == n % 1000)
			break ;
	}
}

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

void	sleeping(t_vars *vars)
{
	gettimeofday(&vars->end_time, NULL);
	printf("%ld %d is sleeping\n", ((vars->end_time.tv_sec - vars->start_time.tv_sec) * 1000) + ((vars->end_time.tv_usec - vars->start_time.tv_usec) / 1000), vars->philosopher);
	my_usleep(vars->time_2_sleep);
}

void	eating(t_vars *vars)
{
	pthread_mutex_lock(&vars->forks);
	pthread_mutex_lock(&(vars + 1)->forks);
	gettimeofday(&vars->end_time, NULL);
	printf("%ld %d has taken a fork\n", ((vars->end_time.tv_sec - vars->start_time.tv_sec) * 1000) + ((vars->end_time.tv_usec - vars->start_time.tv_usec) / 1000), vars->philosopher);
	gettimeofday(&vars->end_time, NULL);
	printf("%ld %d is eating\n", ((vars->end_time.tv_sec - vars->start_time.tv_sec) * 1000) + ((vars->end_time.tv_usec - vars->start_time.tv_usec) / 1000), vars->philosopher);
	my_usleep(vars->time_2_eat);
	pthread_mutex_unlock(&(vars + 1)->forks);
	pthread_mutex_unlock(&vars->forks);
}

void	*philosopher(void *arg)
{
	t_vars *vars = (t_vars *)arg;
	int i = 0;
	while (!vars->notepme || i < vars->notepme)
	{
		gettimeofday(&vars->end_time, NULL);
		printf("%ld %d is thinking\n", ((vars->end_time.tv_sec - vars->start_time.tv_sec) * 1000) + ((vars->end_time.tv_usec - vars->start_time.tv_usec) / 1000), vars->philosopher);
		eating(vars);
		sleeping(vars);
		gettimeofday(&vars->end_time, NULL);
		printf("%ld %d is thinking\n", ((vars->end_time.tv_sec - vars->start_time.tv_sec) * 1000) + ((vars->end_time.tv_usec - vars->start_time.tv_usec) / 1000), vars->philosopher);
		i++;
	}
	return 0;
}

int main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (0);
	int n = ft_atoi(av[1]);
	int eat = ft_atoi(av[2]);
	int die = ft_atoi(av[3]);
	int sleep = ft_atoi(av[4]);
	int notepme = ft_atoi(av[5]);
	t_vars *vars = malloc((n + 1) * sizeof(t_vars));
	int i = -1;
	while (++i < n)
	{
		vars[i].number_of_philos = n;
		vars[i].time_2_eat = eat;
		vars[i].time_2_die = die;
		vars[i].time_2_sleep = sleep;
		vars[i].notepme = notepme;
		vars[i].philosopher = i + 1;
	}
	i = -1;
	while (++i < n)
		pthread_mutex_init(&vars[i].forks, NULL);
	pthread_t *threads = malloc((n + 1) * sizeof(pthread_t));
	i = -1;
	while (++i < n)
	{
		gettimeofday(&vars[i].start_time, NULL);
		pthread_create(&threads[i], NULL, philosopher, &vars[i]);
		my_usleep(1);
	}
	i = -1;
	while (++i < n)
		pthread_join(threads[i], NULL);
	return (0);
}
