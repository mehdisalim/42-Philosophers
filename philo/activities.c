/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:04:26 by esalim            #+#    #+#             */
/*   Updated: 2023/03/25 23:18:11 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	thinking(t_data *data)
{
	print("is thinking", data);
	return (SUCCEEDED);
}

int	eating(t_data *data)
{
	mutex(data, pthread_mutex_lock, 1);
	print("is eating", data);
	pthread_mutex_lock(data->mutex_eat);
	gettimeofday(&data->update_time_2_die, NULL);
	if (data->eater[0] != -1)
		data->eater[0]++;
	pthread_mutex_unlock(data->mutex_eat);
	if (!my_usleep(data, data->args[TIME_2_EAT] * 1000))
		return (FAILED);
	mutex(data, pthread_mutex_unlock, 0);
	return (SUCCEEDED);
}

int	sleeping(t_data *data)
{
	print("is sleeping", data);
	my_usleep(data->args[TIME_2_SLEEP] * 1000);
	return (SUCCEEDED);
}
