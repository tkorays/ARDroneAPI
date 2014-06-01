/**
**************************************************************
* Copyright tkorays(c),2013-2014
*
* @file     ATCmdGenerator.h
* @brief    generate AT command string
* @author   tkorays
* @version  0.3
* @date     2014/6/2
**************************************************************
*/

#ifndef _TK_AT_CMD_GENERATOR_H_
#define _TK_AT_CMD_GENERATOR_H_
#pragma once
#include <iostream>
using namespace std;
#include "CommandId.h"

namespace tk {
	/**
	 * @brief generate single AT command or a AT command package
	 */
	class ATCmdGenerator {
	private:
		CommandId* cmd_id; // manage cmd id
		string cmdpack; // used when pack commands
	public:
		/**
		 * @brief constructor,set CommandId
		 */
		ATCmdGenerator(CommandId* cmdid);

		string cmd_takeoff(); // genetate takeoff AT command
		string cmd_land(); // generate land AT command
		string cmd_emergency(); // generate emergency AT command
		string cmd_move(bool flag, float roll, float pitch, float gaz, float yaw); // generate AT progresive command for moving drone
		string cmd_move_adv(bool flag, float roll, float pitch, float gaz, float yaw, float psi, float psiacr); // generate AT progresive command for full controlling
		string cmd_ftrims(); // generate AT command for flat trims 
		string cmd_calib(int); // generate AT command for magnetometer calibration
		string cmd_config(string name, string value); // generate AT command for configuration
		string cmd_config_ids(string, string, string); // generate AT comamnd in multiconfiguration
		string cmd_watchdog(); // generate AT command for watchdog
		string cmd_control(int,int); // generate AT command for controlling

		// package helper

		/**
		 * @brief add strings into command package
		 */
		void operator<<(const string);
		/** 
		 * @brief add strings into command package,the same as operator "<<"
		 */
		void pack(const string);
		/** 
		 * @brief clear command package for next using
		 */
		void clear_pack();
		/** 
		 * @breif get command package 
		 */
		string get_cmd_pack();
	};
}

#endif // _TK_AT_CMD_GENERATOR_H_