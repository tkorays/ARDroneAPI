#include "include/Mutex.h"
using namespace tk;

Mutex::Mutex() {
	mutex = CreateMutex(NULL, FALSE, NULL);
}
bool Mutex::wait(unsigned long wait_time) {
	DWORD ret = WaitForSingleObject(mutex, wait_time);
	if (ret!=WAIT_OBJECT_0) {
		return false;
	}
	return true;
}
bool Mutex::unlock() {
	if (!ReleaseMutex(mutex)) {
		return false;
	}
	return true;
}