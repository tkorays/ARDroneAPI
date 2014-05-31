//#pragma comment(lib,"ardrone_tk.lib")
#pragma comment(lib,"pthreadVC2.lib")
#pragma comment(lib,"ws2_32.lib")

#include <iostream>
#include <string>
using namespace std;
#include <WinSock2.h>
#include <pthread.h>

#include <helper.h>
#include <ATCmdGenerator.h>
#include <ARDroneControllor.h>
#include <NavDataClient.h>
using namespace tk;


void* ardrone_control_2(void* param) {
	CommandId cmd_id;
	ATCmdGenerator gen(&cmd_id);

	tk::net_prepare();
	ARDroneControllor ctrl;
	int key;
	ctrl.init_at_cmd_ctrl();
	while (true) {
		key = getchar();
		if (key=='x') {
			break;
		}
		switch (key) {
		case 'j':
			ctrl.send_at_cmd_ctrl(gen.cmd_takeoff());
			break;
		case 'k':
			ctrl.send_at_cmd_ctrl(gen.cmd_land());
			break;
		case 'l':
			ctrl.send_at_cmd_ctrl(gen.cmd_emergency());
			break;
		case 'a':
			ctrl.send_at_cmd_ctrl(gen.cmd_move(true, -0.5f, 0.0f, 0.0f, 0.0f));
			break;
		case 'd':
			ctrl.send_at_cmd_ctrl(gen.cmd_move(true, 0.5f, 0.0f, 0.0f, 0.0f));
			break;
		case 'w':
			ctrl.send_at_cmd_ctrl(gen.cmd_move(true, 0.0f, 0.5f, 0.0f, 0.0f));
			break;
		case 's':
			ctrl.send_at_cmd_ctrl(gen.cmd_move(true, 0.0f, -0.5f, 0.0f, 0.0f));
			break;
		default:
			break;
		}
	}
	ctrl.release_at_cmd_ctrl();
	tk::net_end();
	return NULL;
}
void* navdata_recv(void* param) {
	CommandId cmd_id;
	ATCmdGenerator gen(&cmd_id);

	tk::net_prepare();
	ARDroneControllor ctrl;
	ctrl.init_at_cmd_ctrl();
	ctrl.send_at_cmd_ctrl(gen.cmd_land());

	NavDataClient nav;
	nav.exit_bootstrap(ctrl, gen);
	if (!nav.init_navdata_client()) {
		cout << "init navdata_client error" << endl;
		nav.release_navdata_client();
		ctrl.release_at_cmd_ctrl();
		return NULL;
	}
	int len = 1024;
	char* data = new char[1024];
	// Òì²½½ÓÊÕ
	TK_STATUS status;
	while (true) {
		status = nav.recv_pack(data, len);
		if (status==TK_OK) {
			cout << data << endl;
		} else {
			check_status(status, "not receive any data");
		}
	}

	nav.release_navdata_client();
	ctrl.release_at_cmd_ctrl();
	return NULL;
}
int main(int argc,char** argv) {
	cout << "start..." << endl;
	//pthread_t pid;
	//pthread_create(&pid, NULL, ardrone_control, NULL);

	pthread_t pid_nav;
	pthread_create(&pid_nav, NULL, navdata_recv, NULL);

	//pthread_join(pid,NULL);
	pthread_join(pid_nav, NULL);
	return 0;
}