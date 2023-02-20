#include "main.h"

int eating;
int n_philosopher;

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

pthread_mutex_t lock;

void	phil_taken_fork(t_vars *vars)
{
		printf("The philosopher %d has taken a fork\n", vars->n_o_philo);
		vars->fork = 1;
		if (vars->n_o_philo + 2 == vars->numer_of_philos)
			vars[1].fork = 1;
		else if (vars->n_o_philo + 2 > vars->numer_of_philos)
			vars[0].fork = 1;
		else
			vars[vars->n_o_philo + 2].fork = 1;
}

void    phil_eating(t_vars *vars)
{
	pthread_mutex_lock(&lock);
	phil_taken_fork(vars);
	printf("The philosopher %d is eating\n", vars->n_o_philo);
	eating = 1;
	sleep(vars->time_2_eat);
	pthread_mutex_unlock(&lock);
}

void	phil_taken_thinking(t_vars *vars)
{
	pthread_mutex_lock(&lock);
	printf("The philosopher %d is thinking\n", vars->n_o_philo);
	eating = 0;
	pthread_mutex_unlock(&lock);
}

void	phil_taken_died(t_vars *vars)
{

}

void    *phil_sleeping(t_vars *vars)
{ 
	printf("Philosopher %d start sleeping\n", vars->n_o_philo % 5);
	sleep(vars->time_2_sleep);
	printf("Philosopher %d finish sleeping\n", vars->n_o_philo % 5);
	return (0);
}

void    *philosophers(void *args)
{
	phil_eating((t_vars *)args);
	phil_taken_thinking((t_vars *)args);
	pthread_exit(args);
	return (0);
}

void    init_struct(t_vars *vars, char **av)
{
	int i = 0;
	int n = ft_atoi(av[1]);
	while (++i <= n)
	{
		vars->numer_of_philos = n;
		vars->n_o_philo = i;
		vars->time_2_die = ft_atoi(av[2]);
		vars->time_2_eat = ft_atoi(av[3]);
		vars->time_2_sleep = ft_atoi(av[4]);
		vars->notepme = ft_atoi(av[5]);
		vars->fork = 1;
		vars++;
	}
}

int main(int ac, char **av)
{
	if (ac != 6)
		return (0);
	int n = ft_atoi(av[1]) + 1;
	t_vars  *vars = malloc(n * sizeof *vars);
	pthread_mutex_init(&lock, NULL);
	init_struct(vars, av);
	pthread_t *thread_id = malloc(n * sizeof *thread_id);
	int i = 0;
	int j = 0;
	while (++i < n)
	{
		if (i + 2 >= n)
			i = i % 2;
		pthread_create(&thread_id[i], NULL, philosophers, (void *)&vars[i + 2]);
		pthread_join(thread_id[i], (void *)&vars);
	}
	while (++i < n)
	return (0);
}
