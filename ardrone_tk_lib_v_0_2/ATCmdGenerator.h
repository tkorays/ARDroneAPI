#ifndef _TK_AT_CMD_GENERATOR_H_
#define _TK_AT_CMD_GENERATOR_H_
#pragma once
#include <iostream>
using namespace std;
#include "CommandId.h"

namespace tk {
	class ATCmdGenerator {
	private:
		CommandId* cmd_id;
		string cmdpack;
	public:
		ATCmdGenerator(CommandId* cmdid);

		string cmd_takeoff();
		string cmd_land();
		string cmd_emergency();
		string cmd_move(bool flag, float roll, float pitch, float gaz, float yaw);
		string cmd_move_adv(bool flag, float roll, float pitch, float gaz, float yaw, float psi, float psiacr);
		string cmd_ftrims();
		string cmd_calib(int);
		string cmd_config(string, string);
		string cmd_config_ids(string, string, string);
		string cmd_watchdog();
		string cmd_control();

		void operator<<(const string);
		void pack(const string);
		void clear_pack();
		string get_cmd_pack();
	};
}

#endif // _TK_AT_CMD_GENERATOR_H_