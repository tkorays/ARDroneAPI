#include "ControllorGen.h"
#include "comdef.h"
#include "helper.h"
using namespace tk;

#include <sstream>
using namespace std;

ControllorGen::ControllorGen(CommandId* cmdid) {
	cmd_id = cmdid;
}
// generate the takeoff command
string ControllorGen::cmd_takeoff() {
	stringstream cmd_str;
	cmd_str<<"AT*REF=";
	cmd_str << cmd_id->get_id(true)<<","<<512<<LF_DEF;
	return cmd_str.str();
}
// generate land command
string ControllorGen::cmd_land() {
	stringstream cmd_str;
	cmd_str << "AT*REF=";
	cmd_str << cmd_id->get_id(true) << "," << 0 << LF_DEF;
	return cmd_str.str();
}
// generate emergency command
string ControllorGen::cmd_emergency() {
	stringstream cmd_str;
	cmd_str << "AT*REF=";
	cmd_str << cmd_id->get_id(true) << "," << 256 << LF_DEF;
	return cmd_str.str();
}
// generate move command (AT*PCMD)
string ControllorGen::cmd_move(bool enable, float lr, float fb, float vh, float an) {
	stringstream cmd_str;
	cmd_str << "AT*PCMD=";
	cmd_str << cmd_id->get_id(true)<<",";
	if (enable) {
		cmd_str << 1 << ",";
	} else {
		cmd_str << 0 << ",";
	}
	cmd_str << f32_int32_adjust(lr) << ",";
	cmd_str << f32_int32_adjust(fb) << ",";
	cmd_str << f32_int32_adjust(vh) << ",";
	cmd_str << f32_int32_adjust(an) << LF_DEF;
	return cmd_str.str();
}
// generate flat trims command
string ControllorGen::cmd_ftrims() {
	stringstream cmd_str;
	cmd_str << "AT*FTRIM=" << cmd_id->get_id(true) << LF_DEF;
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