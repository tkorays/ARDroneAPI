#include "ControllorGen.h"
#include "comdef.h"
#include "helper.h"
using namespace tk;

#include <sstream>
using namespace std;

ControllorGen::ControllorGen(CommandId* cmdid) {
	cmd_id = cmdid;
}

// AT*REF for takeoff
string ControllorGen::cmd_takeoff() {
	stringstream cmd_str;
	cmd_str<<"AT*REF=";
	cmd_str << cmd_id->get_id(true)<<","<<0x11540200<<CR_DEF;
	return cmd_str.str();
}

// AT*REF for landding
string ControllorGen::cmd_land() {
	stringstream cmd_str;
	cmd_str << "AT*REF=";
	cmd_str << cmd_id->get_id(true) << "," << 0x11540000 << CR_DEF;
	return cmd_str.str();
}

// AT*REF for emergency mod
string ControllorGen::cmd_emergency() {
	stringstream cmd_str;
	cmd_str << "AT*REF=";
	cmd_str << cmd_id->get_id(true) << "," << 0x11540100 << CR_DEF;
	return cmd_str.str();
}

// AT*PCMD for move 
string ControllorGen::cmd_move(bool flag, float lr, float fb, float vh, float an) {
	stringstream cmd_str;
	cmd_str << "AT*PCMD=";
	cmd_str << cmd_id->get_id(true)<<",";
	if (flag) {
		cmd_str << 1 << ",";
	} else {
		cmd_str << 0 << ",";
	}
	cmd_str << f32_int32_adjust(lr) << ","
		<< f32_int32_adjust(fb) << ","
		<< f32_int32_adjust(vh) << ","
		<< f32_int32_adjust(an) << CR_DEF;
	return cmd_str.str();
}

// AT*PCMD_MAG for move
string ControllorGen::cmd_move_mag(bool flag, float lr, float fb, float vh, float an,float psi, float accuracy) {
	stringstream cmd_str;
	cmd_str << "AT*PCMD_MAG=" << cmd_id->get_id(true) << ",";
	if (flag) {
		cmd_str << 1 << ",";
	} else {
		cmd_str << 0 << ",";
	}
	cmd_str << f32_int32_adjust(lr) << ","
		<< f32_int32_adjust(fb) << ","
		<< f32_int32_adjust(vh) << ","
		<< f32_int32_adjust(an) << ","
		<< f32_int32_adjust(psi) << ","
		<< f32_int32_adjust(accuracy) << CR_DEF;
	return cmd_str.str();
}

// AT*FTRIM for flatting trims
string ControllorGen::cmd_ftrims() {
	stringstream cmd_str;
	cmd_str << "AT*FTRIM=" << cmd_id->get_id(true) << CR_DEF;
	return cmd_str.str();
}

// AT*CALIB 
string ControllorGen::cmd_calib(int device) {
	stringstream cmd_str;
	cmd_str << "AT*CALIB=" << cmd_id->get_id(true) << "," << device << CR_DEF;
	return cmd_str.str();
}

// AT*CONFIG for config
string ControllorGen::cmd_config(string name, string value) {
	stringstream cmd_str;
	cmd_str << "AT*CONFIG=" << cmd_id->get_id(true) << ","
		<< "\"" << name << "\"," << "\"" << value << "\"" << CR_DEF;
	return cmd_str.str();
}

// AT*CONFIG_IDS
string ControllorGen::cmd_config_ids(string sid, string uid, string caid) {
	stringstream cmd_str;
	cmd_str << "AT*CONFIG_IDS=" << cmd_id->get_id(true) << ","
		<< "\"" << sid << "\","
		<< "\"" << uid << "\","
		<< "\"" << caid << "\"" << CR_DEF;
	return cmd_str.str();
}

// TODO: sth missing

// AT*COMWDG ,communicate with watch dog
string ControllorGen::cmd_watchdog() {
	return "";
}

string ControllorGen::cmd_control() {
	stringstream cmd_str;
	cmd_str << "AT*CTRL=0" << CR_DEF;
	return cmd_str.str();
}

// pack command
void ControllorGen::operator << (const string cmd) {
	stringstream ss;
	ss << cmdpack;
	ss << cmd;
	cmdpack = ss.str();
}
// pack command
void ControllorGen::pack(const string cmd) {
	(*this) << cmd;
}
// clear pack
void ControllorGen::clear_pack() {
	cmdpack.clear();
}
// get command pack
string ControllorGen::get_cmd_pack() {
	return cmdpack;
}