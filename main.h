#ifndef MAIN_H
# define MAIN_H

#include <stdio.h>
#include <pthread.h>

typedef enum    e_philo
{
    NUMBER_OF_PHILOSOPHERS = 0,
    TIME_TO_DIE = 1,
    TIME_TO_EAT = 2,
    TIME_TO_SLEEP = 3,
    NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT = 4
}   t_philo;

#endif
