#include <ardrone/basic/Timer.h>
using whu::Timer;

// 用于实现定时器功能，可以使用任何方法实现
class Timer::Impl {

};

whu::Timer::Timer() {
	valid = false;
	runing = false;
}
whu::Timer::Timer(uint32_t interval_, void(*call_fun)(void*param), bool auto_start) {
	interval = interval_;
	runing = false;
	// 如果调用的函数错误，则返回
	if (!call_fun) {  
		return;
	}
	valid = true;
	if (auto_start) {
		start();
	}
}

bool whu::Timer::start() {
	// 如果不可用（没初始化）或者正在运行
	if (!valid || runing) { 
		return false;
	}
	call_fun(nullptr);
}


