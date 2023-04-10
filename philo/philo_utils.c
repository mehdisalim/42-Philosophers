/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:14:21 by esalim            #+#    #+#             */
/*   Updated: 2023/04/10 13:57:52 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	print(char *str, t_data *data)
{
	pthread_mutex_lock(&data->mutex_eat[0]);
	if (get_current_time(data->update_time_2_die) >= data->args[TIME_2_DIE])
	{
		pthread_mutex_unlock(&data->mutex_eat[0]);
		return (SUCCEEDED);
	}
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

int	*get_data(int ac, char **av)
{
	int	*data;

	data = malloc(6 * sizeof(*data));
	if (!data)
		return (0);
	data[0] = ft_atoi(av[1]);
	data[1] = ft_atoi(av[2]);
	data[2] = ft_atoi(av[3]);
	data[3] = ft_atoi(av[4]);
	data[4] = 0;
	if (ac == 6)
	{
		data[4] = ft_atoi(av[5]) * data[0];
		if (data[0] % 2)
			data[4] += data[0];
		(data[4])++;
	}
	return (data);
}
