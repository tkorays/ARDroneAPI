#include "NavDataClient.h"
using namespace tk;

NavDataClient::NavDataClient() :bootstrap_mod(true) {
	nav_sck_running = false;
}
void NavDataClient::exit_bootstrap(ARDroneControllor ctrl, ATCmdGenerator& gen){
	string cmd = gen.cmd_config("general:navdata_demo", "FALSE");
	ctrl.send_at_cmd_ctrl(cmd);
	bootstrap_mod = false;
}

bool NavDataClient::init_navdata_client() {
	nav_sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (nav_sck==INVALID_SOCKET) {
		return false;
	}
	
	nav_sck_addr.sin_family = AF_INET;
	nav_sck_addr.sin_addr.S_un.S_addr = inet_addr(ARDRONE_IP);
	nav_sck_addr.sin_port = ntohs(NAVDATA_PORT);

	int status = connect(nav_sck, (sockaddr*)&nav_sck_addr, sizeof(nav_sck_addr));
	if (status == SOCKET_ERROR) {
		return false;
	}
	
	// send a package to NAVDATA_PORT
	status = sendto(nav_sck, "\1", sizeof("\1"), 0, \
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
TK_STATUS NavDataClient::recv_pack(char* data, int len) {
	if (!nav_sck_running) {
		return TK_FAILED;
	}
	int nsize = sizeof(sockaddr_in);
	int status = recvfrom(nav_sck, data, len, 0, \
		(sockaddr*)&nav_sck_addr, &nsize);
	if (status==SOCKET_ERROR) {
		if (WSAEWOULDBLOCK==WSAGetLastError()) {
			return TK_SOCK_ERROR;
		}
		if (WSAECONNRESET==WSAGetLastError()) {
			return TK_SOCK_ERROR;
		}
		cout << WSAGetLastError() << endl;
		return TK_SOCK_ERROR;
	}
	data[nsize] = '\0';
	return TK_OK;
}