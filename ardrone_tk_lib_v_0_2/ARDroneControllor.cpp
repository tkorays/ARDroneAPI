#include "ARDroneControllor.h"
using namespace tk;

ARDroneControllor::ARDroneControllor() {
	at_cmd_sck_running = false;
}

bool ARDroneControllor::init_at_cmd_ctrl() {
	at_cmd_sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (at_cmd_sck==INVALID_SOCKET) {
		return false;
	}
	// optional 
	/*
	sockaddr_in localaddr;
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(AT_PORT);
	localaddr.sin_addr.S_un.S_addr = inet_addr("192.168.1.2");
	bind(at_cmd_sck, (sockaddr*)&localaddr, 0);
	*/

	ardrone_at_addr.sin_family = AF_INET;
	ardrone_at_addr.sin_addr.S_un.S_addr = inet_addr("192.168.1.1");
	ardrone_at_addr.sin_port = ntohs(AT_PORT);
	int status = connect(at_cmd_sck, (sockaddr*)&ardrone_at_addr, sizeof(ardrone_at_addr));
	if (status == SOCKET_ERROR) {
		return false;
	}
	at_cmd_sck_running = true;
	return true;
}
bool ARDroneControllor::send_at_cmd_ctrl(const string cmd) {
	if (cmd.size()<=0 || !at_cmd_sck_running) {
		return false;
	}
	int status = sendto(at_cmd_sck, cmd.data(), cmd.size(), 0, \
		(sockaddr*)&ardrone_at_addr, sizeof(ardrone_at_addr));
	if (status==SOCKET_ERROR) {
		return false;
	}
	return true;
}

bool ARDroneControllor::release_at_cmd_ctrl() {
	closesocket(at_cmd_sck);
	at_cmd_sck_running = false;
	return true;
}