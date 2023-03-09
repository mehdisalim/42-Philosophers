#include "main.h"

int	eating(t_vars *vars) {
	mutex(vars, pthread_mutex_lock);
	if (get_current_time(vars->update_time_2_die) >= vars->time_2_die)
		vars->is_died[0] = 1;
	if (print("has taken a fork", vars) ==  -1)
		return (-1);
	if (print("is eating", vars) == -1)
		return (-1);
	usleep(vars->time_2_eat * 1000);
	gettimeofday(&vars->update_time_2_die, NULL);
	mutex(vars, pthread_mutex_unlock);
	return 0;
}

int main(int ac, char **av) {
	if (ac != 5 && ac != 6)
		return (0);
	int n = ft_atoi(av[1]);
	int die = ft_atoi(av[2]);
	int eat = ft_atoi(av[3]);
	int sleep = ft_atoi(av[4]);
	int notepme = 0;
	if (ac == 6)
		notepme = ft_atoi(av[5]);
	t_vars *vars = malloc((n + 1) * sizeof(t_vars));
	int died = 0;
	int i = -1;
	pthread_mutex_t efork;
	pthread_mutex_init(&efork, NULL);
	while (++i < n)
	{
		vars[i].number_of_philos = n;
		vars[i].time_2_eat = eat;
		vars[i].time_2_die = die;
		vars[i].time_2_sleep = sleep;
		vars[i].eater = 0;
		vars[i].exit = 0;
		vars[i].is_died = &died;
		vars[i].notepme = notepme;
		vars[i].philosopher = i + 1;
		vars[i].exit_fork = &efork;
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
	void *result;
	while (++i < n)
	{
		pthread_join(threads[i], (void *)&result);
		if ((char *)result == 0)
		{
			pthread_mutex_unlock(&vars->exit_fork[0]);
			return (0);
		}
	}
	return (0);
}
