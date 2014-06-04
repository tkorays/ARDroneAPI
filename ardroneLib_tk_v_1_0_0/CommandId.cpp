#include "include/CommandId.h"
using namespace tk;


// TODO  ���̰߳�ȫ�ģ���Ҫ����������֤
// ���Ǳ����򲻻�һֱ������Ϊ�����ܿ��ǣ�����Ҫ������
CommandId& CommandId::Create() {
	static CommandId cmdid;
	cmdid.id = -1;
	return cmdid;
}

void CommandId::operator++() {
	id++;
}

long CommandId::get_id(bool auto_inc) {
	if (auto_inc) {
		++id;
	}
	return id;
}

void CommandId::reset() {
	id = -1;
}