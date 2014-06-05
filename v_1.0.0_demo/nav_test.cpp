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
	// �Ӳ����л�ȡ����
	navdata_t* navdata = (navdata_t*)((data_pack*)param)->data;
	cout << endl << "received..." << endl << endl;
	// ��ʾ����
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
	
	navdata_t navdata; // ���ڱ���navdata
	nav_client.send(cmd.c_str(), 1); // ���������Ի��״̬��Ϣ
	// �����ڻص���������ʹ��һЩ����
	bool recved = nav_client.recv((char*)&navdata, sizeof(navdata), callback);
	if (recved) {
		// �����bootstrapģʽ���˳�bootstrapģʽ
		if (ardrone_get_mask(navdata.ardrone_state,ARDRONE_NAVDATA_BOOTSTRAP)) {
			cmd = gen.cmd_config("general:navdata_demo", "TRUE");
			at_client.send(cmd.c_str(), cmd.size());
		}
	}
		
	recved = nav_client.recv((char*)&navdata, sizeof(navdata), callback);

	// ����һ��ctrl�����������������
	cmd = gen.cmd_control(5, 0);
	at_client.send(cmd.c_str(), cmd.size());

	// ������Դ���һ�����Դ���option���ݵ�callback����
	while (true) {
		recved = nav_client.recv((char*)&navdata, sizeof(navdata), callback);
	}
	
	//}
	
	net_end();
	return 0;
}