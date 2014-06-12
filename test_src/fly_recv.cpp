#include <ardrone/ardrone.h>

using namespace whu;
using namespace whu::ardrone;
#pragma comment(lib,"ARDrone.lib")

ARDroneClient* arClient;

int main(int argc,char** argv){
	arClient = new ARDroneClient();
	arClient->InitARDrone();
	arClient->SendATCmd(arClient->atgen.cmd_watchdog());
	delete arClient;
	return 0;
}
