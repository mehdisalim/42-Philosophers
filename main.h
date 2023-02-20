#ifndef MAIN_H
# define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct  s_vars
{
    int numer_of_philos;
    int n_o_philo;
    int time_2_die;
    int time_2_eat;
    int time_2_sleep;
    int notepme;
    int fork;
}   t_vars;

#endif
