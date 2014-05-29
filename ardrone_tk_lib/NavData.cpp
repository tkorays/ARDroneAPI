#include "NavData.h"
#include "ControllorGen.h"
using namespace tk;


NavData::NavData(CommandSender* cmd_sender, NavDataReceiver* data_rec) {
	sender = cmd_sender;
	receiver = data_rec;
}

void NavData::init() {
	ControllorGen generator(nullptr);
	string cmd_config_str = generator.cmd_config("general:navdata_demo", "TRUE");
	// TODO: network,send AT command
	string cmd_ctrl = generator.cmd_control();

	sender->send(CommandSender::TO_NAV_PORT, cmd_config_str);
	sender->send(CommandSender::TO_NAV_PORT, cmd_ctrl);
}
void NavData::receive(char* data) {
	receiver->receive(data);
}