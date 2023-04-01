/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:14:21 by esalim            #+#    #+#             */
/*   Updated: 2023/04/01 16:54:27 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	print(char *str, t_data *data)
{
	pthread_mutex_lock(&data->mutex_eat[0]);
	pthread_mutex_lock(&data->mutex_print[0]);
	if (data->eater[0] != -1)
		printf("%ld %d %s\n",
			get_current_time(data->start_time), data->args[ID], str);
	pthread_mutex_unlock(&data->mutex_print[0]);
	pthread_mutex_unlock(&data->mutex_eat[0]);
	return (SUCCEEDED);
}

int	mutex(t_data *data, int (*func)(pthread_mutex_t*), int show)
{
	if (func(&data->fork))
		return (ERROR);
	pthread_mutex_lock(&data->mutex_eat[0]);
	if (show || data->eater[0] != -1)
	{
		pthread_mutex_unlock(&data->mutex_eat[0]);
		print("has taken a fork", data);
	}
	pthread_mutex_unlock(&data->mutex_eat[0]);
	if (data->args[ID] == data->args[N_PHILOS] \
		&& func(&(data - data->args[ID] + 1)->fork))
		return (ERROR);
	else if (data->args[ID] && func(&(data + 1)->fork))
		return (ERROR);
	pthread_mutex_lock(&data->mutex_eat[0]);
	if (show || data->eater[0] != -1)
	{
		pthread_mutex_unlock(&data->mutex_eat[0]);
		print("has taken a fork", data);
	}
	pthread_mutex_unlock(&data->mutex_eat[0]);
	return (SUCCEEDED);
}
