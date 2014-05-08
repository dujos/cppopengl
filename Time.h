#ifndef TIME_H
#define TIME_H

#include <Windows.h>

static DWORD ticks = 0;

class Time {

public:
	static void update_time() {
		ticks = GetTickCount();
	}
	
	static void init_time() { 
		ticks = GetTickCount(); 
	}
	
	static void delay_time() {
		DWORD tick = get_time();
		DWORD interval = 100;
		while(GetTickCount() < (tick + interval)) {
			//pass
		}
	}
	
	static DWORD get_time() { 
		return ticks; 
	}
	
	static DWORD get_time_difference() {
		DWORD tick = get_time();
		update_time();
		return get_time() - tick;
	}
};

#endif