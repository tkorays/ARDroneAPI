#pragma comment(lib,"pthreadVC2.lib")
#pragma comment(lib,"ws2_32.lib")
// helper 里面需要
#pragma comment(lib,"iphlpapi.lib")

#include <iostream>
#include <string>
using namespace std;

#include <WinSock2.h>
#include <pthread.h>

#include <ATCmdGenerator.h>
#include <ARDroneControllor.h>
#include <NavDataClient.h>
#include <helper.h>
using namespace tk;

void* nav_data(void* param) {
	ATCmdGenerator* gen = (ATCmdGenerator*)param;
	NavDataClient nav;
	nav.init_navdata_client();

	ARDroneControllor ctrl;
	
	ctrl.init_at_cmd_ctrl();
	// 返回一些信息，这里不处理了。
	// 工作中应该recv信息，如果是bootstrap模式才会退出bootstrap模式，否则不用。
	// 下面我们不管是不bootstrap模式都发送退出bootstrap模式。

	// 发送控制命令，这里让它呆在原地
	gen->clear_pack();
	gen->pack(gen->cmd_control(5, 0));
	gen->pack(gen->cmd_land());
	gen->pack(gen->cmd_move(false, 0, 0, 0, 0));
	ctrl.send_at_cmd_ctrl(gen->get_cmd_pack());
	
	// 退出bootstrap模式，也可以调用：
	//nav.exit_bootstrap(ctrl, *gen);
	ctrl.send_at_cmd_ctrl(gen->cmd_config("general:navdata_demo", "TRUE"));
	
	// 不断接受数据，当然，这里会接收NAVDATA_PORT初始发的一些状态信息
	char data[1024];
	while (true) {
		int ret = nav.recv_pack(data, 1024);
		if (ret == TK_OK) {
			cout << ret << endl;
		} else {
			check_status(ret, "no data received...");
		}
		//ctrl.send_at_cmd_ctrl(gen->cmd_watchdog());
	}
	ctrl.release_at_cmd_ctrl();
	return NULL;
}

int main(int argc, char** argv) {
	tk::net_prepare();
	
	CommandId cmd_id;
	ATCmdGenerator gen(&cmd_id);

	cout << "start fetch navdata..." << endl;
	pthread_t pid;
	pthread_create(&pid, NULL, nav_data, (void*)&gen);
	pthread_join(pid, NULL);

	

	tk::net_end();
	return 0;
}
