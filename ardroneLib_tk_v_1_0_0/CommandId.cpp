#include "include/CommandId.h"
using namespace tk;

// 这些函数为私有，不能直接调用
CommandId::CommandId() {}
CommandId::CommandId(const CommandId&) {}
const CommandId& CommandId::operator=(const CommandId&) {}

// TODO  非线程安全的，需要互斥锁来保证
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