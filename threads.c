#include "main.h"

void	*philosopher(void *arg) {
	t_data *data = (t_data *)arg;
	if (gettimeofday(&data->update_time_2_die, NULL) == ERROR)
		return (0);
	thinking(data);
	while (eating(data) \
			&& sleeping(data) \
			&& (!data->args[N_O_T_E_P_M_E] \
			|| data->eater[0] <= data->args[N_O_T_E_P_M_E]) \
			&& thinking(data));
	mutex(data, pthread_mutex_unlock, 0);
	pthread_mutex_unlock(data->mutex_eat);
	pthread_mutex_unlock(data->exit_fork);
	return (SUCCEEDED);
}
