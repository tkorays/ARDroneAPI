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
NavDataClient nav_client(&gen,&at_client);
int collect=0;

// ����ֱ�Ӷ�ATCmdClient���б������ָ��
// �����������࣬�����ṩ��dispatch�������ڵ���ʱ��Ҫ�û�����

// �̺߳������������Ź�ָ��
thread_dw_ret th_1_fun(LPVOID param) {
	// ATCmdClient��ʼ��
	at_client.init_at_cmd_client();
	while (true) {
		// ʵ�������˶����������gen��cmd_id
		// ��Ҫ�������ط�ʹ����Щ����ʱ��Ҫ�û�����
		mutex_atc.wait(INF);
		at_cmd cmd;
		cmd.cmd = gen.cmd_watchdog();
		cmd.id = gen.get_current_id();
		// ����atָ���ӵ��б��뷢�ͻ���
		// ��������ֱ��sendû�л����������ܱ�֤���һ��
		//at_client.send_at_cmd(gen.cmd_watchdog());
		at_client.add_cmd_to_list(cmd);
		mutex_atc.unlock();
		Sleep(100); // �������߳̿��Է���
	}
	return 0;
}
// �̺߳�������ʼ��NavClient������߳�3��ATCmdClient׼���ý�������ʱ���򲻶Ϸ���һЩָ��
thread_dw_ret th_2_fun(LPVOID param) {
	mutex_atc.wait(INF);
	nav_client.init_navdata_client();
	mutex_atc.unlock();
	while (true) {
		
		if (collect==0) {
			continue;
		}
		mutex_atc.wait(INF);
		at_cmd cmd;
		cmd.cmd = gen.cmd_ftrims();
		cmd.id = gen.get_current_id();
		nav_client.dispatch_at_cmd(cmd);
		mutex_atc.unlock();
		Sleep(100);
	}
	return 0;
}
// �Ѽ������̷߳��͹�����ATָ�ִ��
thread_dw_ret th_3_fun(LPVOID param) {
	collect = 1;
	at_client.collect_and_send();
	return 0;
}

// �̱߳��������������԰��̱߳����main��������
__CLAIM_THREAD_TABLE__

int main(int argc,char** argv) {
	net_prepare();

	THREAD_TABLE_EXEC();

	mutex_atc.release();

	net_end();
	return 0;
}

// �̱߳������̸߳���
// �������߳��޲������޷���ֵ�ȣ��ܼ򵥵�һ���汾
THREAD_TABLE_START(3)
CREATE_THREAD(th_1_fun)
CREATE_THREAD(th_2_fun)
CREATE_THREAD(th_3_fun)
THREAD_TABLE_END