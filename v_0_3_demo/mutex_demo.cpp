#pragma comment(lib,"ardroneLib_tk_v_0_3.lib")

#include <tk_ardrone.h>
#include <iostream>
#include <string>

using namespace tk;
using namespace std;

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

int main(int argc, char** argv) {
	Thread t[2];
	DWORD th_1_id;
	t[0] = CreateThread(NULL, 0, th_1_fun, NULL, 0, &th_1_id);

	DWORD th_2_id;
	t[1] = CreateThread(NULL, 0, th_2_fun, NULL, 0, &th_2_id);

	WaitForMultipleObjects(2,t,TRUE,INF);
	
	mutex_a.release();
	return 0;
}