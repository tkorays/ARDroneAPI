#include <ardrone/config.h>
#include <ardrone/at/CommandId.h>
#include <ardrone/at/ATCmdGenerator.h>
#include <ardrone/basic/Mutex.h>
#include <ardrone/net/UdpClient.h>
#include <ardrone/basic/helper.h>
#include <ardrone/basic/basic_struct.h>
#include <ardrone/navdata/common.h>
#include <ardrone/navdata/state.h>
#include <ardrone/basic/kbpress.h>
#include <ardrone/basic/timer.h>
#include <iostream>
using namespace std;
using namespace whu;
using namespace whu::ardrone;

#pragma comment(lib,"ARDrone.lib")

UdpClient* recvClient;

void data_recv_func(void* param) {
	// 这里面接收数据
	char data[2048];
	recvClient->recv(data, 2048, nullptr); // 回调函数传入的参数为data
	const navdata_t* nvdt = (navdata_t*)data;
	system("cls");
	cout << " header: " << nvdt->header << endl;
	cout << " vision: " << nvdt->vision_defined << endl;
	
}

int main(int argc,char** argv) {
	net_prepare();
	recvClient = new UdpClient(ARDRONE_IP, NAVDATA_PORT);
	if (!recvClient->is_valid()) {
		cout << "udp client invalid..." << endl;
		return 0;
	}
	cout << "Recieve data every 50ms.." << endl;
	Timer timer(50, data_recv_func, nullptr, false);
	timer.start();

	net_end();
	return 0;
}