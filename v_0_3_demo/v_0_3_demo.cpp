#pragma comment(lib,"ardroneLib_tk_v_0_3.lib")

#include <tk_ardrone.h>
#include <iostream>
#include <string>
using namespace tk;
using namespace std;

CommandId cmd_id;
ATCmdGenerator gen(&cmd_id);

// navdata 处理函数
DWORD WINAPI handle_nav_data(LPVOID lpParam) {
	Sleep(200);
	NavDataClient* client = (NavDataClient*)lpParam;
	client->init_navdata_client();
	return 0;
}

DWORD WINAPI handle_at_cmd_client(LPVOID lpParam) {
	ATCmdClient* client = (ATCmdClient*)lpParam;

	client->init_at_cmd_client();
	//client->send_at_cmd(gen.cmd_land());
	at_cmd cmd;

	cmd.cmd = gen.cmd_land();
	cmd.id = gen.get_current_id();
	client->add_cmd_to_list(cmd);

	cmd.cmd = gen.cmd_land();
	cmd.id = gen.get_current_id();
	client->add_cmd_to_list(cmd);

	// 程序会在此处阻塞
	STATUS status = client->collect_and_send();
	check_status(status, "at client collect and send");
	return 0;
}

int main(int argc, char** argv) {
	cout << "runing..." << endl;
	STATUS status;
	net_prepare();
	
	ATCmdClient at_cmd_client;

	DWORD hATThreadId;
	HANDLE hATThread = CreateThread(NULL, 0, \
		handle_at_cmd_client, \
		&at_cmd_client, \
		0, \
		&hATThreadId);


	NavDataClient nav_data_client(&gen, &at_cmd_client);
	// create threads and handle them
	DWORD hNavThreadId;
	HANDLE hNavThread = CreateThread(NULL, 0, \
		handle_nav_data, \
		&nav_data_client, \
		0, \
		&hNavThreadId);
	
	
	HANDLE hThreads[2];
	hThreads[0] = hATThread;
	hThreads[1] = hNavThread;
	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);
	//WaitForSingleObject(hNavThread, INFINITE);

	nav_data_client.release_navdata_client();
	at_cmd_client.stop_collect();
	at_cmd_client.release_at_cmd_client();
	net_end();
	return 0;
}



