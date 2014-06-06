#ifndef _TK_TIMER_H_
#define _TK_TIMER_H_
#include "type.h"

namespace whu {
	class Timer {
	private:
		class Impl;
		Impl* impl;
		uint32_t interval;
		bool valid;
		bool runing;
		void (*call_fun)(void* param);
	public:
		Timer();
		Timer(uint32_t interval_, void(*call_fun)(void*param),bool auto_start = true);
		bool start();
		static void sleep(uint32_t sleep_time);
	};
}

#endif // _TK_TIMER_H_