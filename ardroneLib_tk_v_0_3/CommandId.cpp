#include "include/CommandId.h"
using namespace tk;

CommandId::CommandId() {
	id = -1;
}
CommandId::~CommandId() {
	mutex_release();
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
long CommandId::get_id(bool auto_inc) {
	mutex_wait(INF);
	if (auto_inc) {
		id++;
	}
	mutex_unlock();
	return id;
}
bool CommandId::mutex_wait(unsigned long wait_time) {
	return id_mutex.wait(wait_time);
}
bool CommandId::mutex_unlock() {
	return id_mutex.unlock();
}
bool CommandId::mutex_release() {
	return id_mutex.release();
}