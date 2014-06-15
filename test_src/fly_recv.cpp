#include <ardrone/ardrone.h>

using namespace whu;
using namespace whu::ardrone;
#pragma comment(lib,"ARDrone.lib")

ARDroneClient* arClient;
bool is_onland = true;

bool kb_control(void*) {
	if (key_press(KEY_SPACE)) {
		if (is_onland) {
			arClient->SendATCmd(arClient->atgen.cmd_takeoff());
			Timer::sleep(2000);
			is_onland = false;
		} else {		
			arClient->SendATCmd(arClient->atgen.cmd_land());
			Timer::sleep(2000);
			is_onland = true;
		}
	}
	if (key_press(KEY_LEFT)) {
		arClient->SendATCmd(arClient->atgen.cmd_move(true, -0.2f, 0.0f, 0.0f, 0.0f));
	}
	if (key_press(KEY_RIGHT)) {
		arClient->SendATCmd(arClient->atgen.cmd_move(true, 0.2f, 0.0f, 0.0f, 0.0f));
	}
	if (key_press(KEY_UP)) {
		arClient->SendATCmd(arClient->atgen.cmd_move(true, 0.0f, -0.2f, 0.0f, 0.0f));
	}
	if (key_press(KEY_DOWN)) {
		arClient->SendATCmd(arClient->atgen.cmd_move(true, 0.0f, 0.2f, 0.0f, 0.0f));
	}
	if (key_press(KEY_RETURN)) {
		return false;
	}
	return true;
}
DWORD WINAPI recv_data(PVOID param) {

	return 0;
}

int main(int argc,char** argv){
	arClient = new ARDroneClient();
	arClient->InitARDrone();
	// ���Ϳ��Ź�
	arClient->SendATCmd(arClient->atgen.cmd_watchdog());
	// flat trims
	arClient->SendATCmd(arClient->atgen.cmd_ftrims());
	// ���Ϳ��Ź�
	arClient->SendATCmd(arClient->atgen.cmd_watchdog());
	
	// ���̿���
	Timer timer_ctrl(50,kb_control,nullptr,false);
	timer_ctrl.start();

	delete arClient;
	return 0;
}
