/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:08:14 by esalim            #+#    #+#             */
/*   Updated: 2023/03/25 23:18:15 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

long	get_current_time(t_time start_time)
{
	long	time;
	t_time	end_time;

	gettimeofday(&end_time, NULL);
	time = (end_time.tv_sec - start_time.tv_sec) * 1000;
	time += (end_time.tv_usec - start_time.tv_usec) / 1000;
	return (time);
}

int	my_usleep(t_data *data, long usec)
{
	t_time	begin;
	long	start;
	long	end;
	long	now;

	gettimeofday(&begin, NULL);
	start = begin.tv_sec * 1000000 + begin.tv_usec;
	end = start + usec;
	while (1)
	{
		if (!checker(data))
			return (FAILED);
		gettimeofday(&begin, NULL);
		now = begin.tv_sec * 1000000 + begin.tv_usec;
		if (now >= end)
			break ;
		usleep(10);
	}
	return (SUCCEEDED);
}
