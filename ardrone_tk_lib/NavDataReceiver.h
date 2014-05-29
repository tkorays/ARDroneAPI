#ifndef _TK_NAVDATA_RECEIVER_H_
#define _TK_NAVDATA_RECEIVER_H_
#pragma once

namespace tk {
	class NavDataReceiver {
	public:
		NavDataReceiver();
		void receive(char* data);
	};
}


#endif // _TK_NAVDATA_RECEIVER_H_