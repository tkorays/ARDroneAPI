#pragma comment(lib,"ardroneLib_tk_v_0_3.lib")

#include <tk_ardrone.h>
#include <iostream>
#include <string>
using namespace tk;

CommandId cmd_id;
ATCmdGenerator gen(&cmd_id);

ATCmdClient at_client;
// 某个时间只允许一个线程对ATCmdClient中增加指令，控制使用范围，可以锁定ATCmdGenerator和CommandId
Mutex mutex_atc;
// 传入参数，是为了给ATCmdClient分配指令任务
NavDataClient nav_client(&gen, &at_client);
int collect = 0;
int atc_ready = 0;

void* show_data(void*);

// 发送飞行指令
thread_dw_ret fly_func(LPVOID param) {
	// ATCmdClient初始化
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
	cout << "请按CTRL+C退出吧..." << endl;
	return 0;
}
// 线程函数，初始化NavClient，如果线程3的ATCmdClient准备好接受数据时，则不断发送一些指令
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
// 搜集其他线程发送过来的AT指令，执行
thread_dw_ret at_cmd_func(LPVOID param) {
	collect = 1;
	at_client.collect_and_send();
	return 0;
}

// 线程表声明，这样可以把线程表放在main函数后面
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
	// 刷数据时候就限制输入指令
	mutex_atc.wait(INF);
	navdata_callback_param* param = (navdata_callback_param*)data;
	console_color_set(0xE);
	cout << param->len << endl;
	cout << "data:" << endl << param->data << endl;
	console_color_reset();
	mutex_atc.unlock();
	return (void*)0;
}