#include "main.h"

int	print(char *str, t_data *data){
	if (pthread_mutex_lock(&data->exit_fork[0]) == -1)
		return -1;
	pthread_mutex_lock(data->mutex_eat);
	if (data->eater[0] != -1)
		printf("%ld %d %s\n", get_current_time((data->start_time)[0]), data->args[ID], str);
	pthread_mutex_unlock(data->mutex_eat);
	if (pthread_mutex_unlock(&data->exit_fork[0]) == -1)
		return -1;
	return (0);
}

int	print_die(t_data *data) {
	if (pthread_mutex_lock(&data->exit_fork[0]) == -1)
		return -1;
	if (pthread_mutex_lock(data->mutex_eat) == -1)
		return ERROR;
	if (data->eater[0] == -1)
	{
		pthread_mutex_unlock(data->mutex_eat);
		pthread_mutex_unlock(&data->exit_fork[0]);
		return ERROR;
	}
	printf("%ld %d died\n", get_current_time((data->start_time)[0]), data->args[ID]);
	data->eater[0] = -1;
	if (pthread_mutex_unlock(data->mutex_eat) == -1)
		return ERROR;
	my_usleep(500);
	if (pthread_mutex_unlock(&data->exit_fork[0]) == -1)
		return ERROR;
	return (SUCCEEDED);
}

int mutex(t_data *data, int (*func)(pthread_mutex_t*), int show) {
	if (func(&data->fork))
		return ERROR;
	if (show)
		print("has taken a fork", data);
	if(data->args[N_PHILOS] == 1)
		return (FAILED);
	if (data->args[ID] == data->args[N_PHILOS] && func(&(data - data->args[ID] + 1)->fork))
		return ERROR;
	else if (data->args[ID] && func(&(data + 1)->fork))
		return ERROR;
	if (show)
		print("has taken a fork", data);
	return (SUCCEEDED);
}

int checker(t_data *data)
{
	if (get_current_time(data->update_time_2_die) >= data->args[TIME_2_DIE])
		print_die(data);
	pthread_mutex_lock(data->mutex_eat);
	if (data->args[N_O_T_E_P_M_E] && (data->eater[0] >= data->args[N_O_T_E_P_M_E] || data->eater[0] < 0))
	{
		pthread_mutex_unlock(data->mutex_eat);
		return (FAILED);
	}
	pthread_mutex_unlock(data->mutex_eat);
	return (SUCCEEDED);
}
