#ifndef _TK_HELPER_
#define _TK_HELPER_
#pragma once

#include <string>
using namespace std;
#include "comdef.h"

namespace tk {
	int f32_int32_adjust(const float);
	void net_prepare();
	void net_end();
	void check_status(TK_STATUS status,const string msg);
}




#endif // _TK_HELPER_