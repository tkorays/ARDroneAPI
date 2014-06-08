#include <ardrone/basic/kbpress.h>
using namespace whu;

bool key_press(int key) {
	if (GetKeyState(key)<0) {
		return true;
	}
	return false;
}