#include <ardrone/ardrone.h>

using namespace whu;
using namespace whu::ardrone;
#pragma comment(lib,"ARDrone.lib")

ARDroneClient* arClient;

int main(int argc,char** argv){
	arClient = new ARDroneClient();
	arClient->InitARDrone();
	// ���Ϳ��Ź�
	arClient->SendATCmd(arClient->atgen.cmd_watchdog());
	// ���
	arClient->SendATCmd(arClient->atgen.cmd_takeoff());
	// ���Ʒ���
	arClient->SendATCmd(arClient->atgen.cmd_move(true, -0.8f, 0.0f, 0.0f,0.0f));
	// ����
	arClient->SendATCmd(arClient->atgen.cmd_land());
	delete arClient;
	return 0;
}
