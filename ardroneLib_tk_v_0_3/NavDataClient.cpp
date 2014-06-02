#include "include/NavDataClient.h"
#include "include/basic_struct.h"
#include "include/helper.h"
using namespace tk;

#include <Windows.h>

/////////////////////////////////////////////////////////////////////////

STATUS NavDataClient::init_socket() {
	nav_sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (nav_sck == INVALID_SOCKET) {
		return TK_INVALID_SCK;
	}
	nav_sck_addr.sin_family = AF_INET;
	nav_sck_addr.sin_addr.S_un.S_addr = inet_addr(ARDRONE_IP);
	nav_sck_addr.sin_port = ntohs(NAVDATA_PORT);

	int status = connect(nav_sck, (sockaddr*)&nav_sck_addr, sizeof(nav_sck_addr));
	if (status == SOCKET_ERROR) {
		return TK_SOCK_ERROR;
	}
	nav_sck_running = true;
	return TK_OK;
}
STATUS NavDataClient::send_data(const char* dt,int len) {
	if (!nav_sck_running) {
		return TK_ERROR;
	}
	int status = sendto(nav_sck, dt, len, 0, \
		(sockaddr*)&nav_sck_addr, sizeof(nav_sck_addr));
	if (status==SOCKET_ERROR) {
		return TK_SOCK_ERROR;
	}
	return TK_OK;
}

////////////////////////////////////////////////////////////////////////////
NavDataClient::NavDataClient() {}

NavDataClient::NavDataClient(ATCmdGenerator* gen, ATCmdClient* client) :bootstrap_mod(true) {
	nav_sck_running = false;
	wait_and_recv = false;
	cmd_gen = gen;
	at_cmd_client = client;
}

STATUS NavDataClient::init_navdata_client() {
	int status = init_socket();
	if (status!=TK_OK) {
		return TK_SOCK_ERROR;
	}

	// send a package to NAVDATA_PORT
	status = send_data(NAV_INIT_PKG, sizeof(NAV_INIT_PKG));
	if (status!=TK_OK) {
		return TK_SOCK_ERROR;
	}
	
	char data[MAX_BUFF_SIZE];
	//const bool* isBootstrap = (bool*)recv_pack(data, MAX_BUFF_SIZE, bootstrap_check);
	// TODO callback function & recv fucntion 
	bool isBootstrap;
	isBootstrap = true;
	if (isBootstrap) {
		// exit bootstrap mode
		at_cmd cmd;
		cmd.cmd = cmd_gen->cmd_config("general:navdata_demo","TRUE");
		cmd.id = cmd_gen->get_current_id();
		dispatch_at_cmd(cmd);
	}

	return TK_OK;
}

STATUS NavDataClient::release_navdata_client() {
	closesocket(nav_sck);
	nav_sck_running = false;
	return TK_OK;
}
STATUS NavDataClient::recv_pack(char* data, int len, void* (*callback)(void*param)) {
	if (!nav_sck_running) {
		return TK_ERROR;
	}
	int nsize = sizeof(sockaddr_in);

	int status = recvfrom(nav_sck, data, len, 0, \
		(sockaddr*)&nav_sck_addr, &nsize);
	if (status==SOCKET_ERROR) {
		return TK_SOCK_ERROR;
	}
	// when data is received , call the callback function to do something
	navdata_callback_param param;
	param.len = len;
	param.data = data;

	callback(&param);
	return TK_OK;
}

STATUS NavDataClient::dispatch_at_cmd(at_cmd cmd) {
	DWORD ret = WaitForSingleObject(at_cmd_client->hMutex, INFINITE);
	if (ret!=WAIT_OBJECT_0) {
		return TK_MUTEX_ERROR;
	}
	at_cmd_client->add_cmd_to_list(cmd);
	ReleaseMutex(at_cmd_client->hMutex);
	return TK_OK;
}


