#include "main.h"

void	init(int ac, char **av, t_vars **var)
{
	t_vars *vars = *var;
	int n = ft_atoi(av[1]);
	int die = ft_atoi(av[2]);
	int eat = ft_atoi(av[3]);
	int sleep = ft_atoi(av[4]);
	int notepme = INT_MAX;
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
	if ((ac != 5 && ac != 6) || check_args(ac, av) == -1)
	{
		write(2, "Invalid Argemments !!\n", 22);
		return (1);
	}
	int n = ft_atoi(av[1]);
	t_vars *vars = malloc((n + 1) * sizeof(t_vars));
	init(ac, av, &vars);
	pthread_t *threads = malloc((n + 1) * sizeof(pthread_t));
	int i;
	i = -1;
    struct timeval start_time;
	gettimeofday(&start_time, NULL);
	while (++i < n)
	{
		vars[i].start_time = &start_time;
		pthread_create(&threads[i], NULL, philosopher, &vars[i]);
		if (vars[i].philosopher % 2 != 0)
			my_usleep(50);
	}
	i = -1;
	while(++i < n)
	{
		pthread_join(threads[i], NULL);
		if (vars->eater[0] == -1)
			break ;
	}
	return (0);
}
