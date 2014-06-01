#ifndef _TK_NAVDATA_CLIENT_H_
#define _TK_NAVDATA_CLIENT_H_
#pragma once
#include "ARDroneControllor.h"
#include "ATCmdGenerator.h"
#include <WinSock2.h>

namespace tk {
	class NavDataClient {
	private:
		bool bootstrap_mod;
		SOCKET nav_sck;
		sockaddr_in nav_sck_addr;
		sockaddr_in localaddr;
		bool nav_sck_running;
	public:
		NavDataClient();
		void exit_bootstrap(ARDroneControllor ctrl,ATCmdGenerator& gen);
		bool init_navdata_client();
		bool release_navdata_client();
		TK_STATUS recv_pack(char* data,int len);
	};
}
#endif // _TK_NAVDATA_CLIENT_H_