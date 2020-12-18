#include "timer.h"
#include <stdio.h>

void init_time() {
	#ifdef TSCTIMER
	printf("TIMER TSC USAGE\n");
	#else
	printf("TIMER CLOCK_GETTIME USAGE\n");
	#endif
}

struct time_object get_time() {
	struct time_object time;

	#ifdef TSCTIMER
	time.ticks = rdtscp();
	#else
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time.time);
	#endif

	return time;
}

uint64_t diff_time(struct time_object end, struct time_object start) {
	#ifdef TSCTIMER
	uint64_t ticks = end - start;
	return ticks;

	// TODO convert to nanoseconds if possible???
	
	#else
	double seconds = difftime(end.time.tv_sec, start.time.tv_sec);
	
	int64_t secs = 0; 
	if(seconds > 0.0) {
	  secs = (int64_t)seconds;
	}
	
	uint64_t total_time = (uint64_t)((secs * 1000000000L) + (int64_t)(end.time.tv_nsec - start.time.tv_nsec));

	return total_time;
	#endif
}
