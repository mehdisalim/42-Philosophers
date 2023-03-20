#include "main.h"

int	init(int ac, char **av, t_data **var)
{
	t_data *data = *var;
	int n = ft_atoi(av[1]);
	int die = ft_atoi(av[2]);
	int eat = ft_atoi(av[3]);
	int sleep = ft_atoi(av[4]);
	int notepme = 0;
	if (ac == 6)
		notepme = ft_atoi(av[5]) * n;
	static int e = 0;
	int i = -1;
	static pthread_mutex_t efork;
	static pthread_mutex_t mutex_eat;
	pthread_mutex_init(&efork, NULL);
	pthread_mutex_init(&mutex_eat, NULL);
	while (++i < n) {
		data[i].args[ID] = i + 1;
		data[i].args[N_PHILOS] = n;
		data[i].args[TIME_2_EAT] = eat;
		data[i].args[TIME_2_DIE] = die;
		data[i].args[TIME_2_SLEEP] = sleep;
		data[i].args[N_O_T_E_P_M_E] = notepme;
		data[i].eater = &e;
		data[i].exit_fork = &efork;
		data[i].mutex_eat = &mutex_eat;
		pthread_mutex_init(&data[i].fork, NULL);
	}
	return (SUCCEEDED);
}

/**
 * @brief 
 * 
 * @param ac number of args
 * @param av value of args
 * @return int 
 */
int main(int ac, char **av)
{
	if ((ac != 5 && ac != 6) || check_args(ac, av) == -1)
	{
		write(2, "Invalid Argemments !!\n", 22);
		return (1);
	}
	int n = ft_atoi(av[1]);
	t_data *data = malloc((n + 1) * sizeof(t_data));
	if (!data)
		return (1);
	init(ac, av, &data);
	pthread_t *threads = malloc((n + 1) * sizeof(pthread_t));
	int i;
	i = -1;
    struct timeval start_time;
	gettimeofday(&start_time, NULL);
	while (++i < n)
	{
		data[i].start_time = &start_time;
		pthread_create(&threads[i], NULL, philosopher, &data[i]);
		if (data[i].args[ID] % 2 != 0)
			my_usleep(10);
	}
	i = -1;
	while(++i < n)
	{
		pthread_join(threads[i], NULL);
		if (data->eater[0] == -1)
			break ;
	}
	return (0);
}
