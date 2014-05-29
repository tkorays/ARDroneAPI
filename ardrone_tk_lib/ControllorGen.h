#ifndef _TK_CONTROLLOR_GEN_H_
#define _TK_CONTROLLOR_GEN_H_
#pragma once
#include <iostream>
using namespace std;
#include "CommandId.h"

namespace tk {
	class ControllorGen {
	private:
		CommandId* cmd_id;
		string cmdpack;
	public:
		ControllorGen(CommandId* cmdid);
		string cmd_takeoff();
		string cmd_land();
		string cmd_emergency();
		string cmd_move(bool,float,float,float,float);
		void operator<<(const string);
		void pack(const string);
		void clear_pack();
		string get_cmd_pack();
	};
}

#endif // _TK_CONTROLLOR_GEN_H_