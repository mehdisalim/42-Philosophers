#include "main.h"

// void my_usleep(unsigned int microseconds) {
//     struct timeval start_time, current_time;
// 	long	elapsed;
//     gettimeofday(&start_time, NULL);
//     while (1) {
//         gettimeofday(&current_time, NULL);
//         elapsed = (current_time.tv_sec - start_time.tv_sec) * 1000000 + (current_time.tv_usec - start_time.tv_usec);
//         if (elapsed >= microseconds)
//             break;
// 			usleep(2);
//     }
// }

long	ft_atoi(const char *str){
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

long	get_current_time(struct timeval start_time){
	long	time;
	struct timeval end_time;
	gettimeofday(&end_time, NULL);
	time = (end_time.tv_sec - start_time.tv_sec) * 1000;
	time += (end_time.tv_usec - start_time.tv_usec) / 1000;
	return (time);
}

void	print(char *str, t_vars *vars){
	printf("%ld %d %s\n", get_current_time(vars->start_time), vars->philosopher, str);
}

int mutex(t_vars *vars, int (*func)(pthread_mutex_t*)) {
	if (func(&vars->fork))
		return (-1);
	if (vars->philosopher >= vars->number_of_philos && func(&(vars - vars->philosopher + 1)->fork))
		return (-1);
	else if (func(&(vars + 1)->fork))
		return (-1);
	else
		return (0);
}

int	eating(t_vars *vars, int *exit) {
	mutex(vars, pthread_mutex_lock);
	if (get_current_time(vars->update_time_2_die) > vars->time_2_die)
	{
		vars->is_died[0] = 1;
		mutex(vars, pthread_mutex_unlock);
		// return (0);
	}
	print("has taken a fork", vars);
	print("is eating", vars);
	gettimeofday(&vars->update_time_2_die, NULL);
	usleep(vars->time_2_eat * 1000);
	(*exit)++;
	mutex(vars, pthread_mutex_unlock);
	return (1);
}

int checker(t_vars *vars) {
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

void	*philosopher(void *arg) {
	t_vars *vars = (t_vars *)arg;
	int i = 0;
	static int exit;
	gettimeofday(&vars->update_time_2_die, NULL);
	while (!vars->notepme || i < vars->notepme)
	{
		if (checker(vars) || vars->is_died[0])
		{
			if (vars->is_died[0])
				print("died", vars);
			return (0);
		}
		print("is thinking", vars);
		eating(vars, &exit);
		if (get_current_time(vars->update_time_2_die) > vars->time_2_die)
			vars->is_died[0] = 1;
		if (checker(vars) || vars->is_died[0])
		{
			if (vars->is_died[0])
				print("died", vars);
			return (0);
		}
		print("is sleeping", vars);	
		if (get_current_time(vars->update_time_2_die) > vars->time_2_die)
			return 0;
		usleep(vars->time_2_sleep * 1000);
		if (checker(vars) || vars->is_died[0])
		{
			if (vars->is_died[0])
				print("died", vars);
			return (0);
		}
		print("is thinking", vars);
		i++;
	}
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
	void *result;
	while (++i < n)
		pthread_join(threads[i], (void *)&result);
	return (0);
}
