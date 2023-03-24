/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalim <esalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:23:46 by esalim            #+#    #+#             */
/*   Updated: 2023/03/24 15:38:40 by esalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR       -1
# define FAILED      0
# define SUCCEEDED   1

# define CHECKER(data) if (!checker(data)) return (FAILED);

typedef struct timeval	t_time;

typedef enum e_args
{
	N_PHILOS,
	ID,
	TIME_2_DIE,
	TIME_2_EAT,
	TIME_2_SLEEP,
	N_O_T_E_P_M_E,
	ENUM_LENGTH
}	t_args;

typedef struct s_data
{
	int				args[ENUM_LENGTH];
	int				*eater;
	pthread_mutex_t	*mutex_eat;
	pthread_mutex_t	*exit_fork;
	pthread_mutex_t	fork;
	t_time			start_time;
	t_time			update_time_2_die;
}	t_data;

// threads.c
void	*philosopher(void *arg);
void	*monitoring(void *args);

// times.c
long	get_current_time(t_time start_time);
int		my_usleep(t_data *data, long usec);

// philo_utils.c
int		mutex(t_data *data, int (*func)(pthread_mutex_t*), int show);
int		print_die(t_data *data);
int		checker(t_data *data);
int		print(char *str, t_data *data);

// check_args.c
int		ft_atoi(const char *str);
int		check_args(int ac, char **av);

// activities.c
int		eating(t_data *data);
int		thinking(t_data *data);
int		sleeping(t_data *data);

#endif
