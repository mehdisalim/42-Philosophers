#ifndef MAIN_H
# define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct  s_vars
{
    int number_of_philos;
    int philosopher;
    int time_2_die;
    int time_2_eat;
    int time_2_sleep;
    int *is_died;
    int exit;
    int notepme;
    int eater;
	pthread_mutex_t fork;
	pthread_mutex_t *exit_fork;
    struct timeval start_time;
    struct timeval update_time_2_die;
}   t_vars;

void	*philosopher(void *arg);
long	get_current_time(struct timeval start_time);
int	    print(char *str, t_vars *vars);
int     mutex(t_vars *vars, int (*func)(pthread_mutex_t*));
int     checker(t_vars *vars);
long	ft_atoi(const char *str);
int	eating(t_vars *vars);

#endif

