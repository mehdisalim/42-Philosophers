/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:11:16 by esalim            #+#    #+#             */
/*   Updated: 2023/03/29 21:05:33 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int checker(t_data *data)
{
	int res;
	pthread_mutex_lock(&data->mutex_eat[0]);
	res = (!data->args[N_O_T_E_P_M_E] || data->eater[0] <= data->args[N_O_T_E_P_M_E] + 1);
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
			&& checker(data)
			&& thinking(data))
		;
	// pthread_mutex_unlock(&data->mutex_eat[0]);
	mutex(data, pthread_mutex_unlock, 0);
	pthread_mutex_unlock(data->mutex_eat);
	pthread_mutex_unlock(data->mutex_print);
	return (0);
}

/*
void	*thread1(void *args)
{
	t_data *data = (t_data *)args;
	int i = -1;
	int n = data->args[N_PHILOS] / 2;
	static int returnValue = 1;
	while(++i < n)
	{
		if (data[i].args[N_O_T_E_P_M_E] && data[i].eater[0] >= data[i].args[N_O_T_E_P_M_E])
			return (&returnValue);
		if (get_current_time(data[i].update_time_2_die) >= data[i].args[TIME_2_DIE])
		{
			pthread_mutex_lock(&data->mutex_print[0]);
			printf("%ld %d died\n", get_current_time(data[i].start_time), data[i].args[ID]);
			return (&returnValue);
		}
	}
	return (0);
}

void	*thread2(void *args)
{
	t_data *data = (t_data *)args;
	int i = data->args[N_PHILOS] / 2 - 2;
	int n = data->args[N_PHILOS];
	static int returnValue = 1;
	while(++i < n)
	{
		if (data[i].args[N_O_T_E_P_M_E] && data[i].eater[0] >= data[i].args[N_O_T_E_P_M_E])
			return (&returnValue);
		if (get_current_time(data[i].update_time_2_die) >= data[i].args[TIME_2_DIE])
		{
			pthread_mutex_lock(&data->mutex_print[0]);
			printf("%ld %d died\n", get_current_time(data[i].start_time), data[i].args[ID]);
			return (&returnValue);
		}
	}
	return (0);
}
*/