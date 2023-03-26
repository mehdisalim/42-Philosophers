/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:04:26 by esalim            #+#    #+#             */
/*   Updated: 2023/03/26 23:20:30 by esalim           ###   ########.fr       */
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
	gettimeofday(&data->update_time_2_die, NULL);
	pthread_mutex_lock(data->mutex_eat);
	data->eater[0]++;
	pthread_mutex_unlock(data->mutex_eat);
	my_usleep(data->args[TIME_2_EAT] * 1000);
	mutex(data, pthread_mutex_unlock, 0);
	return (SUCCEEDED);
}

int	sleeping(t_data *data)
{
	print("is sleeping", data);
	my_usleep(data->args[TIME_2_SLEEP] * 1000);
	return (SUCCEEDED);
}
