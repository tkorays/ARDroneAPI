#ifndef _TK_COMMAND_SENDER_H_
#define _TK_COMMAND_SENDER_H_
#pragma once

#include <string>
using namespace std;

namespace tk {
	class CommandSender {
	public:
		CommandSender();
		void send(int,string);
		enum {
			TO_NAV_PORT = 1,
			TO_AT_PORT = 2,
			TO_VIDEO_PORT = 3
		};
	};
}



#endif // _TK_COMMAND_SENDER_H_