#ifndef MAIN_H
# define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct  s_vars
{
    int id;
    int number_of_philos;
    int *philosophers;
    int time_2_die;
    int time_2_eat;
    int time_2_sleep;
    int notepme;
	pthread_mutex_t *forks;
}   t_vars;

#endif
