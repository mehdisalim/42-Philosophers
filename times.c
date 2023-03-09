#include "main.h"


long	get_current_time(struct timeval start_time){
	long	time;
	struct timeval end_time;
	gettimeofday(&end_time, NULL);
	time = (end_time.tv_sec - start_time.tv_sec) * 1000;
	time += (end_time.tv_usec - start_time.tv_usec) / 1000;
	return (time);
}