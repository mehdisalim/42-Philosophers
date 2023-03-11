#include "main.h"

// void *exit_func(void *args)
// {
// 	t_vars *vars = (t_vars *)args;
// 	int i = 0;
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < vars->number_of_philos -1 && get_current_time(vars[i].update_time_2_die) < vars[i].time_2_die)
// 			i++;
// 		if (get_current_time(vars[i].update_time_2_die) >= vars[i].time_2_die)
// 		{
// 			print("died", vars);
// 			pthread_mutex_lock(vars[i].exit_fork);
// 			vars[i].is_died[0] = 1;
// 			break ;
// 		}
// 	}
// 	return ("EXIT");
// }

void	init(int ac, char **av, t_vars **var)
{
	t_vars *vars = *var;
	int n = ft_atoi(av[1]);
	int die = ft_atoi(av[2]);
	int eat = ft_atoi(av[3]);
	int sleep = ft_atoi(av[4]);
	int notepme = 0;
	if (ac == 6)
		notepme = ft_atoi(av[5]);
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
}

int main(int ac, char **av) {
	if (ac != 5 && ac != 6)
		return (0);
	int n = ft_atoi(av[1]);
	t_vars *vars = malloc((n + 1) * sizeof(t_vars));
	init(ac, av, &vars);
	pthread_t *threads = malloc((n + 1) * sizeof(pthread_t));
	int i;
	i = -1;
	while (++i < n)
	{
		if (gettimeofday(&vars[i].start_time, NULL) != 0)
			return (0);
		pthread_create(&threads[i], NULL, philosopher, &vars[i]);
		usleep(5);
	}
	i = -1;
	while(++i < n)
		pthread_join(threads[i], NULL);
	return (0);
}
