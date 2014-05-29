#ifndef _TK_NAVDATA_H_
#define _TK_NAVDATA_H_
#pragma once

#include "CommandSender.h"
#include "NavDataReceiver.h"

namespace tk {
	class NavData {
	private:
		CommandSender* sender;
		NavDataReceiver* receiver;
	public:
		NavData(CommandSender*,NavDataReceiver*);
		void init();
		void receive(char*);
	};
}


#endif // _TK_NAVDATA_H_