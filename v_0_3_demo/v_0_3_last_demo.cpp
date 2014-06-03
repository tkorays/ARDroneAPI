#pragma comment(lib,"ardroneLib_tk_v_0_3.lib")

#include <tk_ardrone.h>
#include <iostream>
#include <string>
using namespace tk;

CommandId cmd_id;
ATCmdGenerator gen(&cmd_id);

ATCmdClient at_client;
// ĳ��ʱ��ֻ����һ���̶߳�ATCmdClient������ָ�����ʹ�÷�Χ����������ATCmdGenerator��CommandId
Mutex mutex_atc;
// �����������Ϊ�˸�ATCmdClient����ָ������
NavDataClient nav_client(&gen, &at_client);
int collect = 0;
int atc_ready = 0;

void* show_data(void*);

// ���ͷ���ָ��
thread_dw_ret fly_func(LPVOID param) {
	// ATCmdClient��ʼ��
	at_client.init_at_cmd_client();
	atc_ready = 1;
	int key=0;
	at_cmd cmd;
	
	while (key!='x') {
		if (key != '\n') {
			cout << "ardrone $ ";
		}
		console_color_set(0xa);
		key = getchar();
		console_color_reset();
		
		switch (key) {
		case 'j':
			mutex_atc.wait(INF);
			cmd.cmd = gen.cmd_takeoff();
			cmd.id = gen.get_current_id();
			at_client.add_cmd_to_list(cmd);
			mutex_atc.unlock();
			console_color_set(0xE);
			cout << "take off..." << endl;
			console_color_reset();
			break;
		case 'k':
			mutex_atc.wait(INF);
			cmd.cmd = gen.cmd_land();
			cmd.id = gen.get_current_id();
			at_client.add_cmd_to_list(cmd);
			mutex_atc.unlock();
			console_color_set(0xE);
			cout << "landing..." << endl;
			console_color_reset();
			break;
		case 'l':
			mutex_atc.wait(INF);
			cmd.cmd = gen.cmd_emergency();
			cmd.id = gen.get_current_id();
			at_client.add_cmd_to_list(cmd);
			mutex_atc.unlock();
			console_color_set(0xE);
			cout << "emergency..." << endl;
			console_color_reset();
			break;
		default:
			break;
		}
	}
	cout << "�밴CTRL+C�˳���..." << endl;
	return 0;
}
// �̺߳�������ʼ��NavClient������߳�3��ATCmdClient׼���ý�������ʱ���򲻶Ϸ���һЩָ��
thread_dw_ret nav_func(LPVOID param) {
	while (true) {
		if (atc_ready==0) {
			continue;
		}
		mutex_atc.wait(INF);
		nav_client.init_navdata_client();
		mutex_atc.unlock();
		break;
	}
	char data[1024];
	nav_client.recv_pack(data,1024,show_data);

	return 0;
}
// �Ѽ������̷߳��͹�����ATָ�ִ��
thread_dw_ret at_cmd_func(LPVOID param) {
	collect = 1;
	at_client.collect_and_send();
	return 0;
}

// �̱߳��������������԰��̱߳����main��������
__CLAIM_THREAD_TABLE__

int main(int argc, char** argv) {
	net_prepare();

	THREAD_TABLE_EXEC();

	mutex_atc.release();

	net_end();
	return 0;
}


THREAD_TABLE_START(3)
CREATE_THREAD(fly_func)
CREATE_THREAD(nav_func)
CREATE_THREAD(at_cmd_func)
THREAD_TABLE_END

void* show_data(void* data) {
	// ˢ����ʱ�����������ָ��
	mutex_atc.wait(INF);
	navdata_callback_param* param = (navdata_callback_param*)data;
	console_color_set(0xE);
	cout << param->len << endl;
	cout << "data:" << endl << param->data << endl;
	console_color_reset();
	mutex_atc.unlock();
	return (void*)0;
}