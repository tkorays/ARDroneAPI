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
NavDataClient nav_client(&gen,&at_client);
int collect=0;

// 可以直接对ATCmdClient的列表中添加指令
// 对于其他的类，可能提供了dispatch方法，在调用时候要用互斥锁

// 线程函数，产生看门狗指令
thread_dw_ret th_1_fun(LPVOID param) {
	// ATCmdClient初始化
	at_client.init_at_cmd_client();
	while (true) {
		// 实际锁定了多个变量，如gen和cmd_id
		// 主要在其他地方使用这些变量时都要用互斥锁
		mutex_atc.wait(INF);
		at_cmd cmd;
		cmd.cmd = gen.cmd_watchdog();
		cmd.id = gen.get_current_id();
		// 尝试at指令并添加到列表与发送互斥
		// 下面这种直接send没有互斥锁，不能保证序号一致
		//at_client.send_at_cmd(gen.cmd_watchdog());
		at_client.add_cmd_to_list(cmd);
		mutex_atc.unlock();
		Sleep(100); // 让其他线程可以访问
	}
	return 0;
}
// 线程函数，初始化NavClient，如果线程3的ATCmdClient准备好接受数据时，则不断发送一些指令
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
// 搜集其他线程发送过来的AT指令，执行
thread_dw_ret th_3_fun(LPVOID param) {
	collect = 1;
	at_client.collect_and_send();
	return 0;
}

// 线程表声明，这样可以把线程表放在main函数后面
__CLAIM_THREAD_TABLE__

int main(int argc,char** argv) {
	net_prepare();

	THREAD_TABLE_EXEC();

	mutex_atc.release();

	net_end();
	return 0;
}

// 线程表，传入线程个数
// 创建的线程无参数，无返回值等，很简单的一个版本
THREAD_TABLE_START(3)
CREATE_THREAD(th_1_fun)
CREATE_THREAD(th_2_fun)
CREATE_THREAD(th_3_fun)
THREAD_TABLE_END