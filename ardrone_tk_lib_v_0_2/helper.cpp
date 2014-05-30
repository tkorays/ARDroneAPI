#include <sstream>
#include <string>
#include <assert.h>
using namespace std;
#include <WinSock2.h>

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
}