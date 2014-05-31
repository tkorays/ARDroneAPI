#include <sstream>
#include <string>
#include <assert.h>
#include <iostream>
using namespace std;
#include <WinSock2.h>
#include "comdef.h"

namespace tk {
	int f32_int32_adjust(const float n) {
		assert(sizeof(int) == sizeof(float));
		const int* num = (int*)&n;
		return *num;
	}
	void net_prepare() {
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
	}
	void net_end() {
		WSACleanup();
	}
	void check_status(TK_STATUS status, const string msg) {
		switch (status) {
		case TK_OK:
			cout << "every thing is ok..." << endl;
			break;
		case TK_FAILED:
			cout << "wrong..." << endl;
			break;
		case TK_SOCK_ERROR:
			cout << "sock error:" << msg << endl;
			break;
		default:
			cout << "undef status" << endl;
			break;
		}
	}
}