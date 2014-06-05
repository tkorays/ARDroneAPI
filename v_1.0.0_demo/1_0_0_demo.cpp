#pragma comment(lib ,"ardroneLib_tk_v_1_0_0.lib")
#include <ardrone.h>
#include <navdata/common.h>
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
	cout << NAVDATA_ZIMMU_3000_TAG << endl;
	cout << NAVDATA_CKS_TAG << endl;
	net_prepare();
	UdpClient at_client(ARDRONE_IP,AT_PORT);
	UdpClient nav_client(ARDRONE_IP, NAVDATA_PORT);
	string cmd = gen.cmd_watchdog();
	at_client.send(cmd.c_str(),cmd.size());
	cmd = "\1";
	nav_client.send(cmd.c_str(), 1);
	cmd = gen.cmd_control(5, 0);
	at_client.send(cmd.c_str(), cmd.size());
	cmd = gen.cmd_config("general:navdata_demo", "TRUE");
	at_client.send(cmd.c_str(), cmd.size());
	Sleep(1000);
	
	// THREAD_TABLE_EXEC();
	net_end();
	return 0;
}

THREAD_TABLE_START(2)
CREATE_THREAD(func_1)
CREATE_THREAD(func_2)
THREAD_TABLE_END