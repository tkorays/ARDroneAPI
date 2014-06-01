#pragma comment(lib,"pthreadVC2.lib")
#pragma comment(lib,"ws2_32.lib")
// helper ������Ҫ
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
	// ����һЩ��Ϣ�����ﲻ�����ˡ�
	// ������Ӧ��recv��Ϣ�������bootstrapģʽ�Ż��˳�bootstrapģʽ�������á�
	// �������ǲ����ǲ�bootstrapģʽ�������˳�bootstrapģʽ��

	// ���Ϳ������������������ԭ��
	gen->clear_pack();
	gen->pack(gen->cmd_control(5, 0));
	gen->pack(gen->cmd_land());
	gen->pack(gen->cmd_move(false, 0, 0, 0, 0));
	ctrl.send_at_cmd_ctrl(gen->get_cmd_pack());
	
	// �˳�bootstrapģʽ��Ҳ���Ե��ã�
	//nav.exit_bootstrap(ctrl, *gen);
	ctrl.send_at_cmd_ctrl(gen->cmd_config("general:navdata_demo", "TRUE"));
	
	// ���Ͻ������ݣ���Ȼ����������NAVDATA_PORT��ʼ����һЩ״̬��Ϣ
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
