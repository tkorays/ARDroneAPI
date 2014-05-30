#include <sstream>
#include <string>
#include <assert.h>
using namespace std;
namespace tk {
	int f32_int32_adjust(const float n) {
		assert(sizeof(int) == sizeof(float));
		const int* num = (int*)&n;
		return *num;
	}
}