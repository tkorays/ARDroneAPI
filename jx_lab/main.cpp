#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"iphlpapi.lib")
#include <Winsock2.h>
#include <IPHlpApi.h>
#include <stdio.h>



int main() {
	DWORD dwRetVal;
	HANDLE hHeap = GetProcessHeap();
	ULONG ulOutBufLen = sizeof(FIXED_INFO);
	//hHeap
	/*
	FIXED_INFO* pFixedInfo;
	IP_ADDRESS_STRING *pIpAddr;
	pFixedInfo = (FIXED_INFO*)HeapAlloc(hHeap, 0, sizeof(FIXED_INFO));
	
	if (GetNetworkParams(pFixedInfo,&ulOutBufLen)==ERROR_BUFFER_OVERFLOW) {
		HeapFree(hHeap, 0, pFixedInfo);
		pFixedInfo = (FIXED_INFO*)HeapAlloc(hHeap, 0, sizeof(FIXED_INFO));
	}
	
	if (dwRetVal = GetNetworkParams(pFixedInfo, &ulOutBufLen)!=NO_ERROR) {
		printf("call to getnetworkparam failed.\n");
	} else {
		printf("hostname:\t%s\n", pFixedInfo->HostName);
		printf("ip addr :\t%s\n", pFixedInfo->DnsServerList.IpAddress.String);
	}
	HeapFree(hHeap, 0, pFixedInfo);
	*/

	MIB_IPADDRTABLE *pIpTable = (MIB_IPADDRTABLE*)HeapAlloc(hHeap, 0, sizeof(MIB_IPADDRTABLE));
	DWORD dwSize = 0;
	in_addr ipaddr;
	ipaddr.S_un.S_addr = ntohl(pIpTable->table[1].dwAddr);
	char *strIpAddr = inet_ntoa(ipaddr);
	if (GetIpAddrTable(pIpTable,&dwSize,0)==ERROR_INSUFFICIENT_BUFFER) {
		HeapFree(hHeap, 0, pIpTable);
		pIpTable = (MIB_IPADDRTABLE*)HeapAlloc(hHeap, 0, dwSize);
	}
	if (dwRetVal = GetIpAddrTable(pIpTable,&dwSize,0)!=NO_ERROR) {
		printf("failed...");
	}
	printf("ip:\t%u.%u.%u.%u\n", \
		pIpTable->table[0].dwAddr & 0x000000FF, \
		(pIpTable->table[0].dwAddr & 0x0000FF00) >> 8, \
		(pIpTable->table[0].dwAddr & 0x00FF0000) >> 16, \
		(pIpTable->table[0].dwAddr & 0xFF000000) >> 24);
	HeapFree(hHeap, 0, pIpTable);
	CloseHandle(hHeap);
	return 0;
}