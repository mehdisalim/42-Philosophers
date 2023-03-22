/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:11:16 by esalim            #+#    #+#             */
/*   Updated: 2023/03/22 10:14:07 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*philosopher(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (gettimeofday(&data->update_time_2_die, NULL) < 0 || !thinking(data))
		return (0);
	while (eating(data) \
			&& sleeping(data) \
			&& (!data->args[N_O_T_E_P_M_E] \
			|| data->eater[0] <= data->args[N_O_T_E_P_M_E]) \
			&& thinking(data))
		;
	mutex(data, pthread_mutex_unlock, 0);
	pthread_mutex_unlock(data->mutex_eat);
	pthread_mutex_unlock(data->exit_fork);
	return (0);
}
