#pragma comment(lib ,"ardroneLib_tk_v_1_0_0.lib")
#include <ardrone.h>
#include <win_thread.h>
#include <iostream>
using namespace tk;
using namespace std;

void callback(void* param) {
	data_pack* dt = (data_pack*)param;
	char* data = (char*)dt->data;
	cout << "收到数据-------------->" << endl;
	console_color_set(6);
	for (size_t i = 0; i < 128; i++) {
		cout << (int)data[i]<< " ";
	}
	console_color_reset();
}

int main(int argc,char** argv) {
	net_prepare();
	cout << "正在接收数据:" << endl;
	UdpClient client(ARDRONE_IP,NAVDATA_PORT);
	char data[128];
	while (true) {
		client.recv(data, 128, callback);
	}
	net_end();
}