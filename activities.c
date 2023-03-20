/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:04:26 by esalim            #+#    #+#             */
/*   Updated: 2023/03/20 20:01:29 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int thinking(t_data *data)
{
	if (!checker(data) || print("is thinking", data) == -1)
		return (FAILED);
    return (SUCCEEDED);
}

int eating(t_data *data)
{
	if (!checker(data) || mutex(data, pthread_mutex_lock, 1) < 0 || !checker(data))
		return (FAILED);
	print("is eating", data);
	pthread_mutex_lock(data->mutex_eat);
	gettimeofday(&data->update_time_2_die, NULL);
	if (data->eater[0] != -1)
		data->eater[0]++;
	pthread_mutex_unlock(data->mutex_eat);
	my_usleep(data->args[TIME_2_EAT] * 1000);
	mutex(data, pthread_mutex_unlock, 0);
	CHECKER(data);
	return (SUCCEEDED);
}

int sleeping(t_data *data)
{
	CHECKER(data);
	print("is sleeping", data);
	my_usleep(data->args[TIME_2_SLEEP] * 1000);
	CHECKER(data);
	return (SUCCEEDED);
}