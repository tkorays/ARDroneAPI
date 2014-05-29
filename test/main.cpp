#include <ControllorGen.h>
#include <helper.h>
using namespace tk;

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv) {
	CommandId cmd_id;
	ControllorGen gen(&cmd_id);
	cout << gen.cmd_takeoff();
	cout << gen.cmd_takeoff();
	cout << gen.cmd_land();
	cout << gen.cmd_emergency();

	gen.clear_pack();
	gen<<gen.cmd_takeoff();
	gen << gen.cmd_land();
	cout << gen.get_cmd_pack();
	

	cout << endl << gen.cmd_move(true, 0.8f, 0.8f, -0.8f, -0.8f);
	return 0;
}
