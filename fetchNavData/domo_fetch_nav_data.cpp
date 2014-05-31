#pragma comment(lib,"pthreadVC2.lib")
#pragma comment(lib,"ws2_32.lib")

#include <iostream>
#include <string>
using namespace std;

#include <WinSock2.h>
#include <pthread.h>

#include <ATCmdGenerator.h>
#include <ARDroneControllor.h>
#include <NavDataClient.h>
#include <helper.h>
using namespace tk;

void* nav_data(void* param) {
	ATCmdGenerator* gen = (ATCmdGenerator*)param;
	NavDataClient nav;
	ARDroneControllor ctrl;
	// exit bootstrap mode
	ctrl.send_at_cmd_ctrl(gen->cmd_config("general:navdata_demo", "TRUE"));
	ctrl.send_at_cmd_ctrl(gen->cmd_control());
	nav.init_navdata_client();

	char data[1024];
	while (true) {
		int ret = nav.recv_pack(data, 1024);
		if (ret == TK_OK) {
			cout << ret << endl;
		} else {
			check_status(ret, "no data received...");
		}
	}
	return NULL;
}

int main(int argc, char** argv) {
	tk::net_prepare();

	CommandId cmd_id;
	ATCmdGenerator gen(&cmd_id);

	cout << "start fetch navdata..." << endl;

	pthread_t pid;
	pthread_create(&pid, NULL, nav_data, (void*)&gen);
	pthread_join(pid, NULL);

	tk::net_end();
	return 0;
}
