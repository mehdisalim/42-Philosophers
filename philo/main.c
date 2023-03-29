/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:28:42 by esalim            #+#    #+#             */
/*   Updated: 2023/03/29 16:07:06 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	init(int ac, char **av, t_data **var)
{
	t_data *data = *var;
	int n = ft_atoi(av[1]);
	int die = ft_atoi(av[2]);
	int eat = ft_atoi(av[3]);
	int sleep = ft_atoi(av[4]);
	int notepme = 0;
	if (ac == 6)
		notepme = ft_atoi(av[5]);
	int i = -1;
	static pthread_mutex_t m_print;
	static pthread_mutex_t mutex_eat;
	if (pthread_mutex_init(&m_print, NULL) || pthread_mutex_init(&mutex_eat, NULL))
		return (ERROR);
	while (++i < n) {
		data[i].args[ID] = i + 1;
		data[i].args[N_PHILOS] = n;
		data[i].args[TIME_2_EAT] = eat;
		data[i].args[TIME_2_DIE] = die;
		data[i].args[TIME_2_SLEEP] = sleep;
		data[i].args[N_O_T_E_P_M_E] = notepme;
		data[i].eater = 1;
		data[i].mutex_print = &m_print;
		data[i].mutex_eat = &mutex_eat;
		if (pthread_mutex_init(&data[i].fork, NULL))
			return (ERROR);
	}
	return (SUCCEEDED);
}

int main(int ac, char **av)
{
	if ((ac != 5 && ac != 6) || check_args(ac, av) == -1)
	{
		write(2, "Invalid Argemments !!\n", 22);
		return (1);
	}
	int n = ft_atoi(av[1]);
	t_data *data = malloc((n + 1) * sizeof(t_data));
	if (!data)
		return (1);
	if(init(ac, av, &data) == ERROR)
		return (1);
	pthread_t *threads = malloc((n + 1) * sizeof(pthread_t));
	int i;
	i = -1;
    struct timeval start_time;
	if (!threads || gettimeofday(&start_time, NULL) < 0)
		return (1);
	while (++i < n)
	{
		gettimeofday(&data[i].start_time, NULL);
		gettimeofday(&data[i].update_time_2_die, NULL);
		if (pthread_create(&threads[i], NULL, philosopher, &data[i]))
			return (1);
		if (data[i].args[ID] % 2 != 0)
			my_usleep(5);
		// my_usleep(10);
	}
	i = -1;
	while (1)
	{
		i = -1;
		while(++i < n)
		{
			if (data[i].eater == -1 || (data[i].args[N_O_T_E_P_M_E] && data[i].eater > data[i].args[N_O_T_E_P_M_E]))
				break;
			if (get_current_time(data[i].update_time_2_die) >= data[i].args[TIME_2_DIE])
			{
				data->eater = -1;
				pthread_mutex_lock(&data->mutex_print[0]);
				printf("%ld %d died\n", get_current_time(data[i].start_time), data[i].args[ID]);
				pthread_mutex_unlock(&data->mutex_print[0]);
				break;
			}
		}
		if (data[i].eater == -1 || (data[i].args[N_O_T_E_P_M_E] && data[i].eater > data[i].args[N_O_T_E_P_M_E]))
		{
			pthread_mutex_unlock(&data->mutex_eat[0]);
			break ;
		}
	}
	i = -1;
	while (++i < n)
		pthread_join(threads[i], NULL);
	free(data);
	free(threads);
	return (0);
}
