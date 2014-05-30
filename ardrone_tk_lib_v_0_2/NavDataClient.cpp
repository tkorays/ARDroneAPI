#include "NavDataClient.h"
using namespace tk;

NavDataClient::NavDataClient() :bootstrap_mod(true) {
	nav_sck_running = false;
}
void NavDataClient::exit_bootstrap(ARDroneControllor ctrl, ATCmdGenerator& gen) {
	ctrl.send_at_cmd_ctrl(gen.cmd_config("general:navdata_demo","TRUE"));
	bootstrap_mod = false;
}

bool NavDataClient::init_navdata_client() {
	nav_sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (nav_sck==INVALID_SOCKET) {
		return false;
	}
	sockaddr_in localaddr;
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(NAVDATA_PORT);
	localaddr.sin_addr.S_un.S_addr = inet_addr(LOCAL_IP);
	bind(nav_sck, (sockaddr*)&localaddr, 0);

	nav_sck_addr.sin_family = AF_INET;
	nav_sck_addr.sin_addr.S_un.S_addr = inet_addr(ARDRONE_IP);
	nav_sck_addr.sin_port = ntohs(NAVDATA_PORT);

	int status = connect(nav_sck, (sockaddr*)&nav_sck_addr, 0);
	if (status == SOCKET_ERROR) {
		return false;
	}
	status = sendto(nav_sck, "AT*CTRL=0\r", sizeof("AT*CTRL=0\r"), 0, \
		(sockaddr*)&nav_sck_addr, sizeof(nav_sck_addr));
	if (status==SOCKET_ERROR) {
		return false;
	}
	return nav_sck_running = true;
}

bool NavDataClient::release_navdata_client() {
	closesocket(nav_sck);
	nav_sck_running = false;
	return true;
}
void NavDataClient::block_recv(char* data,int len) {
	if (!nav_sck_running) {
		return;
	}
	int nsize = sizeof(sockaddr);
	int status = recvfrom(nav_sck, data, len, 0, \
		(sockaddr*)&nav_sck_addr, &nsize);
	data[nsize] = '\0';
	if (status==SOCKET_ERROR) {
		return;
	}
}