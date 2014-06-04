#pragma comment(lib ,"ardroneLib_tk_v_1_0_0.lib")
#include <ardrone.h>
#include <win_thread.h>
#include <iostream>
using namespace tk;
using namespace std;

CommandId& cmd_id = CommandId::Create();
ATCmdGenerator& gen = ATCmdGenerator::Create(&cmd_id);
Mutex cmd_id_mutex;

__CLAIM_THREAD_TABLE__

thread_dw_ret func_1(void* param) {
	int i = 0;
	while (i<1000) {
		cmd_id_mutex.lock(INF);
		Sleep(150);
		cout << "+ " << cmd_id.get_id(true) << endl;
		cmd_id_mutex.unlock();
	}
	return 0;
}
thread_dw_ret func_2(void* param) {
	int i = 0;
	while (i<1000) {
		cmd_id_mutex.lock(INF);
		Sleep(150);
		cout << "* " << cmd_id.get_id(true) << endl;
		cmd_id_mutex.unlock();
	}
	return 0;
}

int main(int argc, char** argv) {
	/*
	cout << gen.cmd_takeoff() << endl;
	cout << gen.cmd_land() << endl;

	gen.clear_pack();
	gen << gen.cmd_calib(1);
	gen << gen.cmd_config("shabi", "yes");
	cout << gen.get_cmd_pack() << endl;
	*/
	THREAD_TABLE_EXEC();

	return 0;
}

THREAD_TABLE_START(2)
CREATE_THREAD(func_1)
CREATE_THREAD(func_2)
THREAD_TABLE_END