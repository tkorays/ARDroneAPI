#include "CommandId.h"
using namespace tk;

CommandId::CommandId() {
	id = 0;
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
long CommandId::get_id(bool auto_inc=true) {
	if (auto_inc) {
		id++;
	}
	return id;
}