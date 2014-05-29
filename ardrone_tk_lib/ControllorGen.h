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
		string cmd_move_mag(bool, float, float, float, float, float, float);
		string cmd_ftrims();
		string cmd_calib(int);
		string cmd_config(string,string);
		string cmd_config_ids(string, string, string);
		string cmd_watchdog();
		string cmd_control();

		void operator<<(const string);
		void pack(const string);
		void clear_pack();
		string get_cmd_pack();
	};
}

#endif // _TK_CONTROLLOR_GEN_H_