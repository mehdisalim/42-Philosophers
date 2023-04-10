/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:28:42 by esalim            #+#    #+#             */
/*   Updated: 2023/04/10 14:06:47 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	init(int *dt, t_data **var)
{
	static pthread_mutex_t	m_print;
	static pthread_mutex_t	mutex_eat;
	static int				e;
	int						i;

	e = 1;
	i = -1;
	if (pthread_mutex_init(&m_print, NULL) \
		|| pthread_mutex_init(&mutex_eat, NULL))
		return (ERROR);
	while (++i < dt[0])
	{
		(*var)[i].args[ID] = i + 1;
		(*var)[i].args[N_PHILOS] = dt[0];
		(*var)[i].args[TIME_2_DIE] = dt[1];
		(*var)[i].args[TIME_2_EAT] = dt[2];
		(*var)[i].args[TIME_2_SLEEP] = dt[3];
		(*var)[i].args[N_O_T_E_P_M_E] = dt[4];
		(*var)[i].eater = &e;
		(*var)[i].mutex_print = &m_print;
		(*var)[i].mutex_eat = &mutex_eat;
		if (pthread_mutex_init(&(*var)[i].fork, NULL))
			return (ERROR);
	}
	return (SUCCEEDED);
}

int	checking_philosophers(t_data *data, int n, int i)
{
	long	time;

	while (++i < n)
	{
		pthread_mutex_lock(&data->mutex_eat[0]);
		if (data->eater[0] == -1 || (data[i].args[N_O_T_E_P_M_E] \
				&& data[i].eater[0] > data[i].args[N_O_T_E_P_M_E]))
		{
			pthread_mutex_unlock(&data->mutex_eat[0]);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_eat[0]);
		time = get_current_time(data[i].update_time_2_die);
		if (time >= data[i].args[TIME_2_DIE])
		{
			pthread_mutex_lock(&data->mutex_eat[0]);
			data->eater[0] = -1;
			pthread_mutex_unlock(&data->mutex_eat[0]);
			pthread_mutex_lock(&data->mutex_print[0]);
			time = get_current_time(data[i].start_time);
			printf("%ld %d died\n", time, data[i].args[ID]);
			break ;
		}
	}
	return (i);
}

void	main2(t_data *data, pthread_t *threads, int n)
{
	int	i;

	while (1)
	{
		i = -1;
		i = checking_philosophers(data, n, i);
		pthread_mutex_lock(&data->mutex_eat[0]);
		if (data->eater[0] == -1 || (data[i].args[N_O_T_E_P_M_E] \
			&& data[i].eater[0] > data[i].args[N_O_T_E_P_M_E]))
		{
			pthread_mutex_unlock(&data->mutex_eat[0]);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_eat[0]);
	}
	i = -1;
	while (++i < n)
		pthread_detach(threads[i]);
}

void	create_threads(pthread_t *threads, t_data *data, int n)
{
	int				i;

	i = -1;
	while (++i < n)
	{
		gettimeofday(&data[i].start_time, NULL);
		gettimeofday(&data[i].update_time_2_die, NULL);
		if (pthread_create(&threads[i], NULL, philosopher, &data[i]))
			return ;
		if (data[i].args[ID] % 2 != 0)
			my_usleep(20);
	}
}

int	main(int ac, char **av)
{
	pthread_t	*threads;
	t_data		*data;
	int			*dt;

	if ((ac != 5 && ac != 6) || check_args(ac, av) == -1)
		return (write(2, "Invalid Argemments !!\n", 22), 1);
	dt = get_data(ac, av);
	threads = malloc((dt[0] + 1) * sizeof(pthread_t));
	data = malloc((dt[0] + 1) * sizeof(t_data));
	if (!threads || !data || !dt || init(dt, &data) == ERROR)
		return (1);
	create_threads(threads, data, dt[0]);
	main2(data, threads, dt[0]);
	free(data);
	free(dt);
	free(threads);
	return (0);
}
