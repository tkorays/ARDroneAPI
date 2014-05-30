//#pragma comment(lib,"ardrone_tk.lib")
#pragma comment(lib,"pthreadVC2.lib")
#pragma comment(lib,"ws2_32.lib")

#include <iostream>
#include <string>
using namespace std;
#include <WinSock2.h>
#include <pthread.h>

#include <ATCmdGenerator.h>
using namespace tk;

void check_status(int status, const string msg) {
	if (status==SOCKET_ERROR) {
		cout << msg << endl;
		exit(0);
	}
}

void* ardrone_control(void* param) {
	WSADATA wsaData;
	int status = WSAStartup(MAKEWORD(2, 2), &wsaData);
	check_status(status, "start up failed...");

	SOCKET send_udp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (send_udp_socket==INVALID_SOCKET) {
		check_status(SOCKET_ERROR, "invalid socket...");
	}
	sockaddr_in localaddr;
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(5556);
	localaddr.sin_addr.S_un.S_addr = inet_addr("192.168.1.2");
	bind(send_udp_socket, (sockaddr*)&localaddr, 0);

	sockaddr_in send_to_addr;
	send_to_addr.sin_family = AF_INET;
	send_to_addr.sin_addr.S_un.S_addr = inet_addr("192.168.1.1");
	send_to_addr.sin_port = ntohs(5556);
	status = connect(send_udp_socket, (sockaddr*)&send_to_addr, sizeof(send_to_addr));
	check_status(status, "connect failed...");

	CommandId cmd_id;
	ATCmdGenerator gen(&cmd_id);

	char key;
	string cmd;
	while (key=getchar(),key!='x') {
		switch (key) {
		case 'j':
			cmd = gen.cmd_takeoff();
			status = sendto(send_udp_socket, cmd.data(), cmd.size(), 0, \
				(sockaddr*)&send_to_addr, sizeof(send_to_addr));
			cout << cmd.data() << endl;
			break;
		case 'k':
			cmd = gen.cmd_land();
			sendto(send_udp_socket, cmd.data(), cmd.size(), 0, \
				(sockaddr*)&send_to_addr, sizeof(send_to_addr));
			cout << cmd.c_str() << endl;
			break;
		case 'l':
			cmd = gen.cmd_emergency();
			sendto(send_udp_socket, cmd.data(), cmd.size(), 0, \
				(sockaddr*)&send_to_addr, sizeof(send_to_addr));
			cout << cmd.c_str() << endl;
			break;
		case 'a':
			cmd = gen.cmd_move(true, -0.5f, 0.0f, 0.0f, 0.0f);
			sendto(send_udp_socket, cmd.data(), cmd.size(), 0, \
				(sockaddr*)&send_to_addr, sizeof(send_to_addr));
			cout << cmd.c_str() << endl;
			break;
		case 'd':
			cmd = gen.cmd_move(true, 0.5f, 0.0f, 0.0f, 0.0f);
			sendto(send_udp_socket, cmd.data(), cmd.size(), 0, \
				(sockaddr*)&send_to_addr, sizeof(send_to_addr));
			cout << cmd.c_str() << endl;
			break;
		default:
			break;
		}
	}
	closesocket(send_udp_socket);
	WSACleanup();
	return NULL;
}

int main(int argc,char** argv) {
	cout << "start..." << endl;
	pthread_t pid;
	pthread_create(&pid, NULL, ardrone_control, NULL);




	pthread_join(pid,NULL);
	return 0;
}