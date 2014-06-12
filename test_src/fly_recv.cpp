#include <ardrone/ardrone.h>

using namespace whu;
using namespace whu::ardrone;
#pragma comment(lib,"ARDrone.lib")

ARDroneClient* arClient;

int main(int argc,char** argv){
	arClient = new ARDroneClient();
	arClient->InitARDrone();
	// 发送看门狗
	arClient->SendATCmd(arClient->atgen.cmd_watchdog());
	// 起飞
	arClient->SendATCmd(arClient->atgen.cmd_takeoff());
	// 控制飞行
	arClient->SendATCmd(arClient->atgen.cmd_move(true, -0.8f, 0.0f, 0.0f,0.0f));
	// 降落
	arClient->SendATCmd(arClient->atgen.cmd_land());
	delete arClient;
	return 0;
}
