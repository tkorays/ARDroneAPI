#include <ardrone/video/VideoEncap.h>
#include <ardrone/video/video_encapsulation.h>
using namespace whu::ardrone;
#include <stdlib.h>
#include <string.h>

VideoEncap::VideoEncap() {
	data = 0;
	data_index = 0;
}

int VideoEncap::TcpPackSize = 1460;

bool VideoEncap::process(void* tcpdata) {
	const parrot_video_encapsulation_t* pave = \
		(parrot_video_encapsulation_t*)tcpdata;
	if (pave->signature[0]=='P' && pave->signature[1]=='a'\
		&& pave->signature[2]=='V' && pave->signature[3]=='E') {
		data_size = pave->payload_size;
		if (data) {
			free(data);
			// �ͷ�ʱ���ǽ�ָ��֪��0����ֹҰָ��
			data = 0;
		}
		data = malloc(data_size);
		if (!data) {
			perror("error on allocating memory...");
			exit(0);
		}
		memcpy(data, (char*)tcpdata + pave->header_size, TcpPackSize - pave->header_size);
		data_index = TcpPackSize - pave->header_size; // �Ѿ���������ô������
		return false;
	} else {
		// ����PaVEͷ����ֱ�Ӹ�������

		// ���һ��,ʣ�µ�����<=1460
		if (data_size-data_index<=TcpPackSize) {
			memcpy((char*)data + data_index, (char*)tcpdata, data_size - data_index);
			// don't care about data_index
			return true;
		}
		// else������ֱ�Ӹ������ݾ�����
		memcpy((char*)data + data_index, (char*)tcpdata, TcpPackSize);
		data_index += TcpPackSize;
		return false;
	}
}