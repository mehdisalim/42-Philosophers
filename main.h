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
    int notepme;
    int eater;
	pthread_mutex_t fork;
    struct timeval start_time;
    struct timeval update_time_2_die;
}   t_vars;

#endif

