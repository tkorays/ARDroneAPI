#include "include/ATCmdClient.h"
#include "include/comdef.h"
using namespace tk;

////////////////////////////////////////////////////

STATUS ATCmdClient::init_socket() {
	at_cmd_sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (at_cmd_sck==INVALID_SOCKET) {
		return TK_SOCK_ERROR;
	}
	at_addr.sin_family = AF_INET;
	at_addr.sin_addr.S_un.S_addr = inet_addr(ARDRONE_IP);
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

long ATCmdClient::get_cmd_smallest_id() {
	if (cmd_list.size()<=0) {
		return -1;
	}
	long smallest_id = cmd_list[0].id;
	for (size_t i = 1; i < cmd_list.size(); i++) {
		if (cmd_list[i].id<smallest_id) {
			smallest_id = cmd_list[i].id;
		}
	}
	return smallest_id;
}
string ATCmdClient::get_cmd_by_id(long id) {
	for (size_t i = 0; i < cmd_list.size(); i++) {
		if (cmd_list[i].id == id) {
			return cmd_list[i].cmd;
		}
	}
	return "";
}
STATUS ATCmdClient::del_cmd_by_id(long id) {
	vector<at_cmd>::const_iterator it = cmd_list.begin();
	while (it!=cmd_list.end()) {
		if (id==(*it).id) {
			it = cmd_list.erase(it);
			return TK_OK;
		}
		it++;
	}
	return TK_OK;
}
///////////////////////////////////////////////////////////////

ATCmdClient::ATCmdClient() {
	at_cmd_sck_running = false;
	wait_and_send = false;
	pre_cmd_id = -1;
}


STATUS ATCmdClient::init_at_cmd_client() {
	hMutex = CreateMutex(NULL, FALSE, NULL);
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
/**
 * @brief collect at commands from other threads.
 * Mutex ensure the cmd_list is accessed by one thread  at one time.
 */
STATUS ATCmdClient::collect_and_send() {
	wait_and_send = true;
	while (wait_and_send) {
		
		// wait until other threads release mutex(don't use cmd_list)
		DWORD ret = WaitForSingleObject(hMutex, INFINITE);
		if (ret!=WAIT_OBJECT_0) {
			return TK_MUTEX_ERROR;
		} // else send cmd
		
		// initial or no commands
		if (cmd_list.size()==0) {
			continue;
		}
		if (pre_cmd_id+1 != get_cmd_smallest_id()) {
			Sleep(WAIT_TIME_OUT);
			pre_cmd_id++;
			continue;
		}// else,send
		string cmd = get_cmd_by_id(pre_cmd_id + 1);
		if (cmd.empty()) {
			return TK_ATCMD_ERROR;
		} // else
		STATUS  status = send_at_cmd(cmd);
		// TODO: delete the cmd
		del_cmd_by_id(pre_cmd_id + 1);
		if (status!=TK_OK) {
			return TK_SOCK_ERROR;
		}
		
		pre_cmd_id++;
		if (!ReleaseMutex(hMutex)) {
			return TK_MUTEX_ERROR;
		}
		Sleep(rand() / 50);
	}
	return TK_OK;
}
STATUS ATCmdClient::add_cmd_to_list(at_cmd cmd) {
	cmd_list.push_back(cmd);
	return TK_OK;
}
/**
* @brief Stop collecting AT commands from other threads.
* It means that client will never block on the collect_and_send unless you recall it.
*/
STATUS ATCmdClient::stop_collect() {
	wait_and_send = false;
	return TK_OK;
}