#include <ControllorGen.h>
#include <helper.h>
using namespace tk;

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv) {
	CommandId cmd_id; // 用来维护编号
	ControllorGen gen(&cmd_id);
	cout << "take off  :\t" << gen.cmd_takeoff();
	cout << "land      :\t" << gen.cmd_land();
	cout << "emergancy :\t" << gen.cmd_emergency();
	cout << "flat trims:\t" << gen.cmd_ftrims();
	cout << "move test :\t" << gen.cmd_move(true, 0.8f, 0.8f, -0.8f, -0.8f);
	cout << "move mag  :\t" << gen.cmd_move_mag(true, 0.8f, 0.1f, -0.1f, -0.2f, -0.3f, 0.3f);
	cout << "calib test:\t" << gen.cmd_calib(1);
	cout << "config    :\t" << gen.cmd_config("xuzhibo", "sb");


	cout << "数据打包发送:" << endl << "-------------------------" << endl;
	gen.clear_pack();
	gen << gen.cmd_takeoff();
	gen << gen.cmd_land();
	cout << gen.get_cmd_pack();
	

	
	return 0;
}
