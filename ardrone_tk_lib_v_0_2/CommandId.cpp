#include "CommandId.h"
using namespace tk;

CommandId::CommandId() {
	id = -1;
}

void CommandId::inc() {
	id++;
}
void CommandId::operator++() {
	inc();
}
void CommandId::reset() {
	id = 0;
}
long CommandId::get_id(bool auto_inc) {
	if (auto_inc) {
		id++;
	}
	return id;
}