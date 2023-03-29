/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:04:26 by esalim            #+#    #+#             */
/*   Updated: 2023/03/29 15:49:16 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	thinking(t_data *data)
{
	// pthread_mutex_lock(&data->mutex_eat[0]);
	// if (data->eater[0] == -1)
	// {
	// 	pthread_mutex_unlock(&data->mutex_eat[0]);
	// 	return (0);
	// }
	// pthread_mutex_unlock(&data->mutex_eat[0]);
	print("is thinking", data);
	return (SUCCEEDED);
}

int	eating(t_data *data)
{
	// pthread_mutex_lock(&data->mutex_eat[0]);
	// if (data->eater[0] == -1)
	// {
	// 	pthread_mutex_unlock(&data->mutex_eat[0]);
	// 	return (0);
	// }
	// pthread_mutex_unlock(&data->mutex_eat[0]);
	mutex(data, pthread_mutex_lock, 1);
	print("is eating", data);
	gettimeofday(&data->update_time_2_die, NULL);
	pthread_mutex_lock(data->mutex_eat);
	if (data->eater != -1)
		data->eater++;
	pthread_mutex_unlock(data->mutex_eat);
	long time = get_current_time(data->start_time);
	my_usleep(data->args[TIME_2_EAT] * 1000);
	while (get_current_time(data->start_time) - time < data->args[TIME_2_EAT])
		my_usleep(100);
	mutex(data, pthread_mutex_unlock, 0);
	return (SUCCEEDED);
}

int	sleeping(t_data *data)
{
	// pthread_mutex_lock(&data->mutex_eat[0]);
	// if (data->eater[0] == -1)
	// {
	// 	pthread_mutex_unlock(&data->mutex_eat[0]);
	// 	return (0);
	// }
	// pthread_mutex_unlock(&data->mutex_eat[0]);
	print("is sleeping", data);
	long time = get_current_time(data->start_time);
	my_usleep(data->args[TIME_2_SLEEP] * 1000);
	while (get_current_time(data->start_time) - time < data->args[TIME_2_SLEEP])
		my_usleep(100);
	return (SUCCEEDED);
}
