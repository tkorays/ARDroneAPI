#include "include/CommandId.h"
using namespace tk;

// ��Щ����Ϊ˽�У�����ֱ�ӵ���
CommandId::CommandId() {}
CommandId::CommandId(const CommandId&) {}
const CommandId& CommandId::operator=(const CommandId&) {}

// TODO  ���̰߳�ȫ�ģ���Ҫ����������֤
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