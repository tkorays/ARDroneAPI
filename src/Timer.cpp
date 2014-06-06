#include <ardrone/basic/Timer.h>
using whu::Timer;

// ����ʵ�ֶ�ʱ�����ܣ�����ʹ���κη���ʵ��
class Timer::Impl {

};

whu::Timer::Timer() {
	valid = false;
	runing = false;
}
whu::Timer::Timer(uint32_t interval_, void(*call_fun)(void*param), bool auto_start) {
	interval = interval_;
	runing = false;
	// ������õĺ��������򷵻�
	if (!call_fun) {  
		return;
	}
	valid = true;
	if (auto_start) {
		start();
	}
}

bool whu::Timer::start() {
	// ��������ã�û��ʼ����������������
	if (!valid || runing) { 
		return false;
	}
	call_fun(nullptr);
}


