#include <ATCmdGenerator.h>
#include <comdef.h>
using namespace tk;

#include <iostream>
#include <string>
using namespace std;

#include <pthread.h>
#pragma comment(lib,"pthreadVC2.lib")

void* simple_gen(void* param) {
	ATCmdGenerator* gen = (ATCmdGenerator*)param;
	pthread_t myid = pthread_self();
	cout << myid.p << "-" << myid.x << endl;
	
	return NULL;
}

int main(int argc, char** argv) {
	CommandId cmd_id; // 用来维护编号
	ATCmdGenerator gen(&cmd_id);
	pthread_t pid;
	pthread_create(&pid, NULL, simple_gen, NULL);
	cout << "take off  :\t" << gen.cmd_takeoff() << endl;
	cout << "land      :\t" << gen.cmd_land() << endl;
	cout << "emergancy :\t" << gen.cmd_emergency() << endl;
	cout << "flat trims:\t" << gen.cmd_ftrims() << endl;
	cout << "move test :\t" << gen.cmd_move(true, 0.8f, 0.8f, -0.8f, -0.8f) << endl;
	cout << "move mag  :\t" << gen.cmd_move_adv(true, 0.8f, 0.1f, -0.1f, -0.2f, -0.8f, -0.8f) << endl;
	cout << "calib test:\t" << gen.cmd_calib(1) << endl;
	cout << "config    :\t" << gen.cmd_config("xuzhibo", "sb") << endl;

	cout << "数据打包发送:" << endl << "-------------------------" << endl;
	gen.clear_pack();
	gen << gen.cmd_takeoff();
	gen << "\n";
	gen << gen.cmd_land();
	gen << "\n";
	cout << gen.get_cmd_pack();
	cout << endl <<endl;


	pthread_join(pid, NULL);
	
	return 0;
}
