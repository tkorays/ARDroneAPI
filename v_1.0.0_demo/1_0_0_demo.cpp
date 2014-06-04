#pragma comment(lib ,"ardroneLib_tk_v_1_0_0.lib")
#include <ardrone.h>
#include <iostream>
using namespace tk;
using namespace std;

CommandId& cmd_id = CommandId::Create();
ATCmdGenerator& gen = ATCmdGenerator::Create(&cmd_id);

int main(int argc, char** argv) {
	
	cout << gen.cmd_takeoff() << endl;
	cout << gen.cmd_land() << endl;

	gen.clear_pack();
	gen << gen.cmd_calib(1);
	gen << gen.cmd_config("shabi", "yes");
	cout << gen.get_cmd_pack() << endl;

	return 0;
}