#include "main.h"


long	get_current_time(struct timeval start_time){
	long	time;
	struct timeval end_time;
	gettimeofday(&end_time, NULL);
	time = (end_time.tv_sec - start_time.tv_sec) * 1000;
	time += (end_time.tv_usec - start_time.tv_usec) / 1000;
	return (time);
}

void my_usleep(long usec) {
    struct timeval begin;
    gettimeofday(&begin, NULL);
    long start = begin.tv_sec * 1000000 + begin.tv_usec;
    long end = start + usec;
	long now;
    while (1) {
        gettimeofday(&begin, NULL);
        now = begin.tv_sec * 1000000 + begin.tv_usec;
        if (now >= end)
            break;
        usleep(50);
    }
}