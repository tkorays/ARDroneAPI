#include "include/CommandId.h"
using namespace tk;

CommandId::CommandId() {
	id = -1;
}
CommandId::~CommandId() {
	
}
void CommandId::inc() {
	id++;
}
void CommandId::operator++() {
	inc();
}
void CommandId::reset() {
	id = -1;
}
/**
 @brief using mutex is useful on read mode
 */
long CommandId::get_id(bool auto_inc) {
	if (auto_inc) {
		id++;
	}
	return id;
}
