#include "ATCmdGenerator.h"
#include "comdef.h"
#include "helper.h"
using namespace tk;

#include <string>
#include <sstream>
using namespace std;
#include <Windows.h>

ATCmdGenerator::ATCmdGenerator(CommandId* cmdid):cmd_id(cmdid) {}

// AT*REF for takeoff
string ATCmdGenerator::cmd_takeoff() {
	char cmd[128];
	sprintf_s(cmd, 128, "AT*REF=%d,%d%c", cmd_id->get_id(true), static_cast<INT32>(TAKEOFF_CODE), CR_DEF);
	return string(cmd);
}
// AT*REF for land
string ATCmdGenerator::cmd_land() {
	char cmd[128];
	sprintf_s(cmd, 128, "AT*REF=%d,%d%c", cmd_id->get_id(true), static_cast<INT32>(LAND_CODE), CR_DEF);
	return string(cmd);
}
// AT*REF for emergency mod
string ATCmdGenerator::cmd_emergency() {
	char cmd[128];
	sprintf_s(cmd, 128, "AT*REF=%d,%d%c", cmd_id->get_id(true), static_cast<INT32>(EMERG_CODE), CR_DEF);
	return string(cmd);
}
// AT*PCMD,progrossive command for moving
string ATCmdGenerator::cmd_move(bool flag, float roll, float pitch, float gaz, float yaw) {
	char cmd[128];
	sprintf_s(cmd, 128, "AT*PCMD=%d,%d,%d,%d,%d,%d%c", \
		cmd_id->get_id(true),\
		flag?1:0,\
		f32_int32_adjust(roll),\
		f32_int32_adjust(pitch),\
		f32_int32_adjust(gaz),\
		f32_int32_adjust(yaw),\
		CR_DEF);
	return string(cmd);
}
// AT*PCMD_MAG for full controlling
string ATCmdGenerator::cmd_move_adv(bool flag, float roll, float pitch, float gaz, float yaw, float psi, float psiacr) {
	char cmd[500];
	int ret = sprintf_s(cmd, "AT*PCMD=%d,%d,%d,%d,%d,%d,%d,%d%c", \
		cmd_id->get_id(true), \
		flag ? 1 : 0, \
		f32_int32_adjust(roll), \
		f32_int32_adjust(pitch), \
		f32_int32_adjust(gaz), \
		f32_int32_adjust(yaw), \
		f32_int32_adjust(psi), \
		f32_int32_adjust(psiacr), \
		CR_DEF);
	return string(cmd);
}
// AT*FTRIM,flat trims
string ATCmdGenerator::cmd_ftrims() {
	char cmd[128];
	sprintf_s(cmd, "AT*FTRIM=%d%c", cmd_id->get_id(true), CR_DEF);
	return string(cmd);
}
// AT*CALIB
string ATCmdGenerator::cmd_calib(int device) {
	char cmd[128];
	sprintf_s(cmd, "AT*CALIB=%d,%d%c", cmd_id->get_id(true), device, CR_DEF);
	return string(cmd);
}
// AT*CONFIG 
string ATCmdGenerator::cmd_config(string name, string value) {
	char cmd[128];
	sprintf_s(cmd, "AT*CONFIG=%d,%s,%s%c", \
		cmd_id->get_id(true), \
		name.c_str(), \
		value.c_str(), \
		CR_DEF);
	return string(cmd);
}
// AT*CONFIG_IDS
string ATCmdGenerator::cmd_config_ids(string sid, string uid, string caid) {
	char cmd[128];
	sprintf_s(cmd, "AT*CONFIG_IDS=%d,%s,%s,%s%c", \
		cmd_id->get_id(true), \
		sid.c_str(), \
		uid.c_str(), \
		caid.c_str(), \
		CR_DEF);
	return string(cmd);
}
// TODO: watch dog
// AT*COMWDG,communicate with watch dog
string ATCmdGenerator::cmd_watchdog() {
	return "";
}
// TODO: AT*CTRL
// AT*CTRL
string ATCmdGenerator::cmd_control() {
	char cmd[128];
	sprintf_s(cmd, "AT*CTRL=0%c", CR_DEF);
	return string(cmd);
}
// pack command
void ATCmdGenerator::operator << (const string cmd) {
	stringstream ss;
	ss << cmdpack;
	ss << cmd;
	cmdpack = ss.str();
}
// pack command
void ATCmdGenerator::pack(const string cmd) {
	(*this) << cmd;
}
// clear pack
void ATCmdGenerator::clear_pack() {
	cmdpack.clear();
}
// get command pack
string ATCmdGenerator::get_cmd_pack() {
	return cmdpack;
}