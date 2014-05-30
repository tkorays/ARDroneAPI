#ifndef _TK_ARDRONE_CONTROLLOR_H_
#define _TK_ARDRONE_CONTROLLOR_H_
#pragma once
#include <WinSock2.h>
#include "comdef.h"
#include <string>
using namespace std;

namespace tk {
	class ARDroneControllor {
	private:
		SOCKET at_cmd_sck;
		sockaddr_in ardrone_at_addr;
		bool at_cmd_sck_running;
	public:
		ARDroneControllor();
		// AT command
		bool init_at_cmd_ctrl();
		bool send_at_cmd_ctrl(const string cmd);
		bool release_at_cmd_ctrl();
	};
}

#endif // _TK_ARDRONE_CONTROLLOR_H_