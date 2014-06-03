#pragma comment(lib,"ardroneLib_tk_v_0_3.lib")

#include <tk_ardrone.h>
#include <iostream>
#include <string>
using namespace tk;

// ����a���Լ��以����
int a = 0;
Mutex mutex_a;
CommandId cmd_id;
ATCmdGenerator gen(&cmd_id);
Mutex mutex_gen;

// �̺߳���
thread_dw_ret th_1_fun(LPVOID param) {
	while (true) {
		mutex_gen.wait(INF);
		string cmd = gen.cmd_watchdog();
		Sleep(10);
		cout << gen.get_current_id() << "cmd:"<< cmd << endl;
		mutex_gen.unlock();
	}
	return 0;
}
// �̺߳���
thread_dw_ret th_2_fun(LPVOID param) {
	while (true) {
		mutex_gen.wait(INF);
		string cmd = gen.cmd_ftrims();
		Sleep(10);
		cout << gen.get_current_id() << "cmd:" << cmd << endl;
		mutex_gen.unlock();
	}
	return 0;
}

// �̱߳��������������԰��̱߳����main��������
__CLAIM_THREAD_TABLE__

int main(int argc,char** argv) {
	THREAD_TABLE_EXEC();
	mutex_a.release();
	return 0;
}

// �̱߳������̸߳���
// �������߳��޲������޷���ֵ�ȣ��ܼ򵥵�һ���汾
THREAD_TABLE_START(2)
CREATE_THREAD(th_1_fun)
CREATE_THREAD(th_2_fun)
CREATE_THREAD(th_2_fun)
THREAD_TABLE_END