/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:04:26 by esalim            #+#    #+#             */
/*   Updated: 2023/03/20 14:20:03 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int thinking(t_vars *vars)
{
	if (get_current_time(vars->update_time_2_die) >= vars->time_2_die)
		print_die(vars);
	if (vars->notepme && (vars->eater[0] >= vars->notepme || vars->eater[0] < 0))
		return (EXIT);
    print("is thinking", vars);
    return (CONTINUE);
}

int eating(t_vars *vars)
{
	if (get_current_time(vars->update_time_2_die) >= vars->time_2_die)
		print_die(vars);
	if (vars->notepme && (vars->eater[0] >= vars->notepme || vars->eater[0] < 0))
		return (EXIT);
    mutex(vars, pthread_mutex_lock, 1);
	if (get_current_time(vars->update_time_2_die) >= vars->time_2_die)
		print_die(vars);
	if (vars->notepme && (vars->eater[0] >= vars->notepme || vars->eater[0] < 0))
		return (EXIT);
	print("is eating", vars);
	pthread_mutex_lock(vars->mutex_eat);
	gettimeofday(&vars->update_time_2_die, NULL);
	if (vars->eater[0] != -1)
		vars->eater[0]++;
	pthread_mutex_unlock(vars->mutex_eat);
	my_usleep(vars->time_2_eat * 1000);
	mutex(vars, pthread_mutex_unlock, 0);
	if (get_current_time(vars->update_time_2_die) >= vars->time_2_die)
		print_die(vars);
	if (vars->notepme && (vars->eater[0] >= vars->notepme || vars->eater[0] < 0))
		return (EXIT);
	return (CONTINUE);
}

int sleeping(t_vars *vars)
{
	if (get_current_time(vars->update_time_2_die) >= vars->time_2_die)
		print_die(vars);
	if (vars->notepme && (vars->eater[0] >= vars->notepme || vars->eater[0] < 0))
		return (EXIT);
	print("is sleeping", vars);
	my_usleep(vars->time_2_sleep * 1000);
	if (get_current_time(vars->update_time_2_die) >= vars->time_2_die)
		print_die(vars);
	if (vars->notepme && (vars->eater[0] >= vars->notepme || vars->eater[0] < 0))
		return (EXIT);
	return (CONTINUE);
}