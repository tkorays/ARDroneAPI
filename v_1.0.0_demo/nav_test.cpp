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

void callback(void* param) {
	data_pack* pack = (data_pack*)param;
	cout << endl << "received..." << endl << endl;
}

int main(int argc, char** argv) {
	net_prepare();

	UdpClient at_client(ARDRONE_IP, AT_PORT);
	UdpClient nav_client(ARDRONE_IP, NAVDATA_PORT);
	string cmd = "\1";
	
	navdata_t navdata;
	nav_client.send(cmd.c_str(), 1); // 发送数据以获得状态信息
	//gen.cmd_land();
	
	//while (true) {

		bool recved = nav_client.recv((char*)&navdata, sizeof(navdata), callback);
		if (recved) {
			printf("header:   0x%x\n", navdata.header);
			printf("state:    0x%x\n", navdata.ardrone_state);
			printf("seq:      0x%x\n", navdata.sequence);
			printf("vision:   0x%x\n", navdata.vision_defined);
			
		}
		cmd = gen.cmd_config("general:navdata_demo", "TRUE");
		at_client.send(cmd.c_str(), cmd.size());
		recved = nav_client.recv((char*)&navdata, sizeof(navdata), callback);
		if (recved) {
			printf("header:   0x%x\n", navdata.header);
			printf("state:    0x%x\n", navdata.ardrone_state);
			printf("seq:      0x%x\n", navdata.sequence);
			printf("vision:   0x%x\n", navdata.vision_defined);

		}
		cmd = gen.cmd_control(5, 0);
		at_client.send(cmd.c_str(), cmd.size());
		recved = nav_client.recv((char*)&navdata, sizeof(navdata), callback);
		if (recved) {
			printf("header:   0x%x\n", navdata.header);
			printf("state:    0x%x\n", navdata.ardrone_state);
			printf("seq:      0x%x\n", navdata.sequence);
			printf("vision:   0x%x\n", navdata.vision_defined);

		}

	//}

	int key=0;

	while (key!='x') {
		key = getchar();
		switch (key) {
		case 'j':
			cmd = gen.cmd_takeoff();
			at_client.send(cmd.c_str(), cmd.size());
			break;
		case 'k':
			cmd = gen.cmd_land();
			at_client.send(cmd.c_str(), cmd.size());
			break;
		default:
			break;
		}
	}
	net_end();
	return 0;
}