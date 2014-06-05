#pragma comment(lib ,"ardroneLib_tk_v_1_0_0.lib")
#include <ardrone.h>
#include <navdata/common.h>
#include <navdata/state.h>
#include <win_thread.h>
#include <iostream>
using namespace tk;
using namespace std;

CommandId& cmd_id = CommandId::Create();
ATCmdGenerator& gen = ATCmdGenerator::Create(&cmd_id);
Mutex cmd_id_mutex;

__CLAIM_THREAD_TABLE__

void callback(void* param) {
	// 从参数中获取数据
	navdata_t* navdata = (navdata_t*)((data_pack*)param)->data;
	cout << endl << "received..." << endl << endl;
	// 显示数据
	printf("header:   0x%x\n", navdata->header);
	printf("state:    0x%x\n", navdata->ardrone_state);
	printf("seq:      0x%x\n", navdata->sequence);
	printf("vision:   0x%x\n", navdata->vision_defined);
}

int main(int argc, char** argv) {
	net_prepare();
	UdpClient at_client(ARDRONE_IP, AT_PORT);
	UdpClient nav_client(ARDRONE_IP, NAVDATA_PORT);
	string cmd = "\1";
	
	navdata_t navdata; // 用于保存navdata
	nav_client.send(cmd.c_str(), 1); // 发送数据以获得状态信息
	// 可以在回调函数里面使用一些功能
	bool recved = nav_client.recv((char*)&navdata, sizeof(navdata), callback);
	if (recved) {
		// 如果是bootstrap模式就退出bootstrap模式
		if (ardrone_get_mask(navdata.ardrone_state,ARDRONE_NAVDATA_BOOTSTRAP)) {
			cmd = gen.cmd_config("general:navdata_demo", "TRUE");
			at_client.send(cmd.c_str(), cmd.size());
		}
	}
		
	recved = nav_client.recv((char*)&navdata, sizeof(navdata), callback);

	// 发送一个ctrl命令，接收连续的数据
	cmd = gen.cmd_control(5, 0);
	at_client.send(cmd.c_str(), cmd.size());

	// 这里可以传入一个可以处理option数据的callback函数
	while (true) {
		recved = nav_client.recv((char*)&navdata, sizeof(navdata), callback);
	}
	
	//}
	
	net_end();
	return 0;
}