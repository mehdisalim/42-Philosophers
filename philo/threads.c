/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:11:16 by esalim            #+#    #+#             */
/*   Updated: 2023/04/05 21:15:00 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	checker(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->mutex_eat[0]);
	res = (!data->args[N_O_T_E_P_M_E] \
		|| data->eater[0] <= data->args[N_O_T_E_P_M_E]);
	pthread_mutex_unlock(&data->mutex_eat[0]);
	return (res);
}

void	*philosopher(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	if (gettimeofday(&data->update_time_2_die, NULL) < 0)
		return (0);
	thinking(data);
	while (eating(data) \
			&& sleeping(data) \
			&& checker(data) \
			&& thinking(data))
		;
	mutex(data, pthread_mutex_unlock, 0);
	pthread_mutex_unlock(data->mutex_eat);
	pthread_mutex_unlock(data->mutex_print);
	return (0);
}
