#include <ardrone/config.h>
#include <ardrone/at/CommandId.h>
#include <ardrone/at/ATCmdGenerator.h>
#include <ardrone/basic/Mutex.h>
#include <ardrone/net/UdpClient.h>
#include <ardrone/basic/helper.h>
#include <ardrone/basic/basic_struct.h>
#include <ardrone/navdata/common.h>
#include <ardrone/navdata/state.h>
#include <iostream>
using namespace std;
using namespace whu;
using namespace whu::ardrone;

#pragma comment(lib,"ARDrone.lib")

CommandId& cmdid = CommandId::Create();
ATCmdGenerator& gen = ATCmdGenerator::Create(&cmdid);

Mutex genMutex;

// ����pack
void exit_bootstrap(void* param) {
	const data_pack* dt = (data_pack*)param;
	// ����ǲ���bootstrapģʽ
	const navdata_t* navdata = (navdata_t*)(dt->data);
	// ����Ͳ�����ͷ�Ƿ��
	if (ardrone_get_mask(navdata->ardrone_state,ARDRONE_NAVDATA_BOOTSTRAP)) {
		cout << "����bootstrapģʽ" << endl;
		genMutex.lock(500);
		gen << gen.cmd_config("general:navdata_demo", "TRUE");
		genMutex.unlock();
	}

}

int main(int argc, char** argv) {
	net_prepare();
	UdpClient atClient(ARDRONE_IP, AT_PORT);
	UdpClient navClient(ARDRONE_IP, NAVDATA_PORT);

	string cmd;
	char recv_data[2048];
	cmd = "\1";
	// init for navdata
	navClient.send(cmd.c_str(), cmd.size());
	navClient.recv(recv_data, 2048, exit_bootstrap);

	// ��gen��pack����Ҫ����
	genMutex.lock(500);
	cmd = gen.get_cmd_pack();
	gen.clear_pack();
	genMutex.unlock();

	if (cmd.size()>0) {
		// ����ָ���˳�bootstrap
		navClient.send(cmd.c_str(),cmd.size());
	}
	// ACK
	cmd = gen.cmd_control(5, 0);
	navClient.send(cmd.c_str(), cmd.size());

	// ��ʼ����ϣ�������ѭ����ȡ��������

	while (true) {

	}

	net_end();
	return 0;
}