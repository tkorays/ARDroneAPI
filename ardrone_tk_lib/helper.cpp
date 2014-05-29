#include <sstream>
#include <string>
using namespace std;
namespace tk {
	string f32_int32_adjust(const float n) {
		float* num = new float;
		*num = n;
		int* num_trans = (int*)num;
		stringstream ss;
		ss << *num_trans;
		delete num;
		return ss.str();
	}
}