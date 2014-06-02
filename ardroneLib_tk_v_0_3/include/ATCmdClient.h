/**
**************************************************************
* Copyright tkorays(c),2013-2014
*
* @file     ATCmdClient.h
* @brief    send AT command
* @author   tkorays
* @version  0.3
* @date     2014/6/2
**************************************************************
*/

#ifndef _TK_AT_CMD_CLIENT_H_
#define _TK_AT_CMD_CLIENT_H_
#pragma once

#include "comdef.h"
#include "basic_struct.h"
#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include <vector>
using namespace std;

namespace tk {
	/**
	 * @brief Manage AT command on a thread.
	 * Collect all AT command send by other threads
	 */
	class ATCmdClient {
	private:
		SOCKET at_cmd_sck; // windows socket ,UDP-5554
		sockaddr_in at_addr; // ardrone address
		bool at_cmd_sck_running; // socket & sockaddr status
		bool wait_and_send; // status for managing collecting commands

		vector<at_cmd> cmd_list;
		long pre_cmd_id;

		STATUS init_socket(); // init socket & sockaddr
		STATUS send_data(const char* dt,int len); // send data to sockaddr

		long get_cmd_smallest_id();
		string get_cmd_by_id(long id);
		STATUS del_cmd_by_id(long id);
	public:
		HANDLE hMutex; // mutex for lock cmd_list
		ATCmdClient();
		STATUS init_at_cmd_client(); // init client
		STATUS send_at_cmd(const string cmd); // send single at command
		STATUS collect_and_send(); // wait and collect AT commands then send them
		STATUS release_at_cmd_client(); // release
		STATUS add_cmd_to_list(at_cmd cmd);
		/**
		 * @brief Stop collecting AT commands from other threads.
		 * It means that client will never block on the collect_and_send unless you recall it.
		 */
		STATUS stop_collect();
	};
}


#endif // _TK_AT_CMD_CLIENT_H_