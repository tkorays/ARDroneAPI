#include <ardrone/basic/Timer.h>
#include <ardrone/os/win/inc.h>
using whu::Timer;

// ����ʵ�ֶ�ʱ�����ܣ�����ʹ���κη���ʵ��
class Timer::Impl {

};

whu::Timer::Timer() {
	valid = false;
	runing = false;
}
whu::Timer::Timer(uint32_t interval_, void(*call_func)(void*param), void* param, bool auto_start) {
	interval = interval_;
	runing = false;
	// ������õĺ��������򷵻�
	if (!call_func) {  
		valid = false;
		return;
	}
	func = call_func;
	func_param = param;
	valid = true;
	if (auto_start) {
		start();
	}
}
// ���д�ıȽϼ�....
bool whu::Timer::start() {
	// ��������ã�û��ʼ����������������
	if (!valid || runing) { 
		return false;
	}
	// ����ò�Ʋ���Բ�������
	while (true) {
		func(func_param);
		Sleep(interval);
	}
	
	return true;
}


void Timer::sleep(uint32_t sleep_time) {
	Sleep(sleep_time);
}
