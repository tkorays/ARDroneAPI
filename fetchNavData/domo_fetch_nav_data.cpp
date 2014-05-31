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
	nav.init_navdata_client();

	ARDroneControllor ctrl;
	// exit bootstrap mode
	ctrl.send_at_cmd_ctrl(gen->cmd_config("general:navdata_demo", "TRUE"));
	//ctrl.send_at_cmd_ctrl("AT*CONFIG=\"general:navdata_demo\",\"TRUE\"\r");
	//ctrl.send_at_cmd_ctrl("AT*CTRL=0");
	ctrl.send_at_cmd_ctrl(gen->cmd_control());

	SOCKET sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in sck_addr;
	sck_addr.sin_addr.S_un.S_addr = inet_addr(ARDRONE_IP);
	sck_addr.sin_family = AF_INET;
	sck_addr.sin_port = ntohs(CONTROL_PORT);
	connect(sck, (sockaddr*)&sck_addr, sizeof(sck_addr));
	sendto(sck, gen->cmd_control().data(), gen->cmd_control().size(), 0, \
		(sockaddr*)&sck_addr, sizeof(sck_addr));

	

	char data[1024];
	while (true) {
		int ret = nav.recv_pack(data, 1024);
		if (ret == TK_OK) {
			cout << ret << endl;
		} else {
			check_status(ret, "no data received...");
		}
		ctrl.send_at_cmd_ctrl(gen->cmd_watchdog());
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
