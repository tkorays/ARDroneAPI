#include <sstream>
#include <string>
#include <assert.h>
#include <iostream>
using namespace std;
#include <WinSock2.h>
#include <IPHlpApi.h>
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
			cout << "every thing is ok:"<< msg << endl;
			break;
		case TK_FAILED:
			cout << "wrong:" << msg << endl;
			break;
		case TK_SOCK_ERROR:
			cout << "sock error:" << msg << endl;
			break;
		default:
			cout << "undef status:" << msg << endl;
			break;
		}
	}


	string get_local_ip() {
		DWORD dwRetVal;
		HANDLE hHeap = GetProcessHeap();
		MIB_IPADDRTABLE *pIpTable = (MIB_IPADDRTABLE*)HeapAlloc(hHeap, 0, sizeof(MIB_IPADDRTABLE));
		DWORD dwSize = 0;
		in_addr ipaddr;
		ipaddr.S_un.S_addr = ntohl(pIpTable->table[1].dwAddr);
		char *strIpAddr = inet_ntoa(ipaddr);
		if (GetIpAddrTable(pIpTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER) {
			HeapFree(hHeap, 0, pIpTable);
			pIpTable = (MIB_IPADDRTABLE*)HeapAlloc(hHeap, 0, dwSize);
		}
		if (dwRetVal = GetIpAddrTable(pIpTable, &dwSize, 0) != NO_ERROR) {
			return "";
			
		}
		char ret[15];
		sprintf_s(ret, "%u.%u.%u.%u", \
			pIpTable->table[0].dwAddr & 0x000000FF, \
			(pIpTable->table[0].dwAddr & 0x0000FF00) >> 8, \
			(pIpTable->table[0].dwAddr & 0x00FF0000) >> 16, \
			(pIpTable->table[0].dwAddr & 0xFF000000) >> 24);
		HeapFree(hHeap, 0, pIpTable);
		CloseHandle(hHeap);
		return string(ret);
	}
}