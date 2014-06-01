#include "include/ATCmdClient.h"
using namespace tk;

////////////////////////////////////////////////////

STATUS ATCmdClient::init_socket() {
	at_cmd_sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (at_cmd_sck==INVALID_SOCKET) {
		return TK_SOCK_ERROR;
	}
	at_addr.sin_family = AF_INET;
	at_addr.sin_addr.S_un.S_addr = inet_addr("192.168.1.1");
	at_addr.sin_port = ntohs(AT_PORT);
	int status = connect(at_cmd_sck, (sockaddr*)&at_addr, sizeof(at_addr));
	if (status == SOCKET_ERROR) {
		TK_SOCK_ERROR;
	}
	at_cmd_sck_running = true;
	return TK_OK;
}

STATUS ATCmdClient::send_data(const char* dt, int len) {
	int status = sendto(at_cmd_sck, dt, len, 0, \
		(sockaddr*)&at_addr, sizeof(at_addr));
	if (status == SOCKET_ERROR) {
		return TK_SOCK_ERROR;
	}
	return TK_OK;
}
///////////////////////////////////////////////////////////////

ATCmdClient::ATCmdClient() {
	at_cmd_sck_running = false;
}


STATUS ATCmdClient::init_at_cmd_client() {
	return init_socket();
}

STATUS ATCmdClient::send_at_cmd(const string cmd) {
	if (cmd.size()<=0 || !at_cmd_sck_running) {
		return TK_ERROR;
	}
	return send_data(cmd.data(), cmd.size());
}

STATUS ATCmdClient::release_at_cmd_client() {
	closesocket(at_cmd_sck);
	at_cmd_sck_running = false;
	return TK_OK;
}