/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:04:26 by esalim            #+#    #+#             */
/*   Updated: 2023/03/14 11:36:53 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int thinking(t_vars *vars)
{
	if (!checker(vars))
		return (EXIT);
    print("is thinking", vars);
	if (!checker(vars))
		return (EXIT);
    return (CONTINUE);
}

int eating(t_vars *vars)
{
	if (!checker(vars))
		return (EXIT);
    mutex(vars, pthread_mutex_lock);
	if (!checker(vars))
			return (EXIT);
	print("has taken a fork", vars);
	print("is eating", vars);
	usleep(vars->time_2_eat * 1000);
	if (!checker(vars))
        return (EXIT);
	gettimeofday(&vars->update_time_2_die, NULL);
	mutex(vars, pthread_mutex_unlock);
	if (!checker(vars))
        return (EXIT);
	return (CONTINUE);
}

int sleeping(t_vars *vars)
{
	if (!checker(vars))
        return (EXIT);
    print("is sleeping", vars);
    usleep(vars->time_2_sleep * 1000);
	if (!checker(vars))
        return (EXIT);
	return (CONTINUE);
}