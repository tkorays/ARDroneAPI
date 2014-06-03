#pragma comment(lib,"ardroneLib_tk_v_0_3.lib")

#include <tk_ardrone.h>
#include <iostream>
#include <string>
using namespace tk;

typedef HANDLE Thread;
#define THREAD_RET DWORD WINAPI

int a = 0;
Mutex mutex_a;

THREAD_RET th_1_fun(LPVOID param) {
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
THREAD_RET th_2_fun(LPVOID param) {
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

__CLAIM_THREAD_TABLE__

int main(int argc,char** argv) {
	THREAD_TABLE_EXEC();
	return 0;
}

THREAD_TABLE_START(2)
CREATE_THREAD(0, th_1_fun)
CREATE_THREAD(1, th_2_fun)
THREAD_TABLE_END(2)