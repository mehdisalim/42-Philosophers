#include "main.h"

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
	static int died = 0;
	static int locker = 0;
	int i = -1;
	static pthread_mutex_t efork;
	static pthread_mutex_t mutex_eat;
	static pthread_mutex_t mutex_lock;
	static int e = 0;
	pthread_mutex_init(&efork, NULL);
	pthread_mutex_init(&mutex_eat, NULL);
	while (++i < n) {
		vars[i].number_of_philos = n;
		vars[i].time_2_eat = eat;
		vars[i].time_2_die = die;
		vars[i].time_2_sleep = sleep;
		vars[i].eater = &e;
		vars[i].exit = 0;
		vars[i].locker = &locker;
		vars[i].is_died = &died;
		vars[i].notepme = notepme;
		vars[i].philosopher = i + 1;
		vars[i].exit_fork = &efork;
		vars[i].mutex_eat = &mutex_eat;
		vars[i].mutex_lock = &mutex_lock;
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
	pthread_t secoud_thread;
	int i;
	i = -1;
	pthread_mutex_lock(vars->mutex_lock);
	while (++i < n)
	{
		gettimeofday(&vars[i].start_time, NULL);
		pthread_create(&threads[i], NULL, philosopher, &vars[i]);
		// my_usleep(10);
	}
	pthread_create(&secoud_thread, NULL, unlocker, &vars[0]);
	i = -1;
	while(++i < n)
		pthread_join(threads[i], NULL);
	return (0);
}
