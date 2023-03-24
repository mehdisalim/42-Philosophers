/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:11:16 by esalim            #+#    #+#             */
/*   Updated: 2023/03/24 17:05:57 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*philosopher(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (gettimeofday(&data->update_time_2_die, NULL) < 0 || !thinking(data))
		return (0);
	while (data->eater[0] > -1 \
			&& eating(data) \
			&& sleeping(data) \
			&& (!data->args[N_O_T_E_P_M_E] \
			|| data->eater[0] <= data->args[N_O_T_E_P_M_E]) \
			&& thinking(data))
		;

	
	if (pthread_mutex_lock(data->mutex_eat) == -1)
		return 0;
	if (data->eater[0] == -1)
	{
		pthread_mutex_unlock(data->mutex_eat);
		pthread_mutex_unlock(&data->exit_fork[0]);
		return 0;
	}
	data->eater[0] = -1;
	if (pthread_mutex_unlock(data->mutex_eat) == -1)
		return 0;
	
	mutex(data, pthread_mutex_unlock, 0);
	pthread_mutex_unlock(data->mutex_eat);
	pthread_mutex_unlock(data->exit_fork);
	return (0);
}