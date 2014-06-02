#ifndef _TK_BASIC_STRUCT_H_
#define _TK_BASIC_STRUCT_H_
#pragma once

#include <string>
using namespace std;

namespace tk {
	typedef struct _navdata_callback_param {
		int len;
		void* data;
	} navdata_callback_param;

	typedef struct _at_cmd {
		long id;
		string cmd;
	} at_cmd;
}
#endif