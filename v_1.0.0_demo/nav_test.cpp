#pragma comment(lib ,"ardroneLib_tk_v_1_0_0.lib")
#include <ardrone.h>
#include <navdata/common.h>
#include <win_thread.h>
#include <iostream>
using namespace tk;
using namespace std;

CommandId& cmd_id = CommandId::Create();
ATCmdGenerator& gen = ATCmdGenerator::Create(&cmd_id);
Mutex cmd_id_mutex;

__CLAIM_THREAD_TABLE__

int main(int argc, char** argv) {
	net_prepare();

	UdpClient at_client(ARDRONE_IP, AT_PORT);
	UdpClient nav_client(ARDRONE_IP, NAVDATA_PORT);
	string cmd = "\1";
	navdata_t navdata;
	nav_client.send(cmd.c_str(), 1); // 发送数据以获得状态信息
	while (true) {
		nav_client.recv((char*)&navdata, sizeof(navdata), nullptr);
		printf("header:%x\n", navdata.header);
		printf("state:%x\n", navdata.ardrone_state);
		printf("seq:%x\n", navdata.sequence);
		printf("vision:%x\n", navdata.vision_defined);
	}

	net_end();
	return 0;
}