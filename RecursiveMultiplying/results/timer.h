#pragma once

#include <stdint.h>

#ifdef TSCTIMER
	#include <unistd.h>
#else
	#include <time.h>
#endif

struct time_object {
#ifdef TSCTIMER
	uint64_t ticks;
#else
	struct timespec time;
#endif	
};

void init_time();

struct time_object get_time();

uint64_t diff_time(struct time_object end, struct time_object start);
