#include "main.h"

void	*philosopher(void *arg) {
	t_vars *vars = (t_vars *)arg;
	int i = 0;
	gettimeofday(&vars->update_time_2_die, NULL);
	while (!vars->notepme || i < vars->notepme)
	{
		if (checker(vars) || vars->is_died[0])
		{
			if (vars->is_died[0])
			{
				if (pthread_mutex_lock(&vars->exit_fork[0]) == -1)
					return (0);
				print("died", vars);
			}
			return (0);
		}
		print("is thinking", vars);
		eating(vars);
		if (get_current_time(vars->update_time_2_die) > vars->time_2_die)
			vars->is_died[0] = 1;
		if (checker(vars) || vars->is_died[0])
		{
			if (vars->is_died[0])
			{
				print("died", vars);
				if (pthread_mutex_lock(&vars->exit_fork[0]) == -1)
					return (0);
			}
			return (0);
		}
		print("is sleeping", vars);	
		if (get_current_time(vars->update_time_2_die) > vars->time_2_die)
			return (0);
		usleep(vars->time_2_sleep * 1000);
		if (checker(vars) || vars->is_died[0])
		{
			if (vars->is_died[0])
			{
				print("died", vars);
				if (pthread_mutex_lock(&vars->exit_fork[0]) == -1)
					return (0);
			}
			return (0);
		}
		print("is thinking", vars);
		i++;
		usleep(1);
	}
	return 0;
}