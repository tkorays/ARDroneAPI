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
#include <WinSock2.h>
#include <string>
using namespace std;

namespace tk {
	class ATCmdClient {
	private:
		SOCKET at_cmd_sck;
		sockaddr_in at_addr;
		bool at_cmd_sck_running;
		STATUS init_socket();
		STATUS send_data(const char* dt,int len);
	public:
		ATCmdClient();
		STATUS init_at_cmd_client();
		STATUS send_at_cmd(const string cmd);
		STATUS collect_and_send();
		STATUS release_at_cmd_client();
	};
}


#endif // _TK_AT_CMD_CLIENT_H_