/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:08:14 by esalim            #+#    #+#             */
/*   Updated: 2023/03/28 22:04:26 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

long	get_current_time(t_time start_time)
{
	t_time	end_time;
	gettimeofday(&end_time, NULL);
	return (((end_time.tv_sec - start_time.tv_sec) * 1000) + ((end_time.tv_usec - start_time.tv_usec) / 1000));
}

void	my_usleep(long usec)
{
	t_time	begin;
	long	end;

	gettimeofday(&begin, NULL);
	end = (begin.tv_sec * 1000000) + begin.tv_usec + usec;
	while (1)
	{
		gettimeofday(&begin, NULL);
		if ((begin.tv_sec * 1000000 + begin.tv_usec) > end)
			break ;
		usleep(50);
	}
}
