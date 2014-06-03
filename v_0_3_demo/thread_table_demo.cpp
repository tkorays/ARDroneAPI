#pragma comment(lib,"ardroneLib_tk_v_0_3.lib")

#include <tk_ardrone.h>
#include <iostream>
#include <string>
using namespace tk;

// 变量a，以及其互斥锁
int a = 0;
Mutex mutex_a;

// 线程函数
thread_dw_ret th_1_fun(LPVOID param) {
	while (true) {
		mutex_a.wait(INF);
		if (a<1000) {
			a++;
		} else {
			break;
		}
		Sleep(10);
		cout << a << endl;
		mutex_a.unlock();
	}
	return 0;
}
// 线程函数
thread_dw_ret th_2_fun(LPVOID param) {
	while (true) {
		mutex_a.wait(INF);
		if (a<1000) {
			a += 2;
		} else {
			break;
		}
		Sleep(10);
		cout << a << "*" << endl;
		mutex_a.unlock();
	}
	return 0;
}

// 线程表声明，这样可以把线程表放在main函数后面
__CLAIM_THREAD_TABLE__

int main(int argc,char** argv) {
	THREAD_TABLE_EXEC();
	return 0;
}

// 线程表，传入线程个数
// 创建的线程无参数，无返回值等，很简单的一个版本
THREAD_TABLE_START(2)
CREATE_THREAD(th_1_fun)
CREATE_THREAD(th_2_fun)
CREATE_THREAD(th_2_fun)
THREAD_TABLE_END