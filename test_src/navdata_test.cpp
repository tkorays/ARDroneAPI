#include <ardrone/navdata/common.h>
#include <iostream>
using namespace whu::ardrone;
using namespace std;

#pragma comment(lib,"ARDrone.lib")

int main(int argc,char** argv) {
	cout << "navdata��С(����һ��option��������checksum):" << sizeof(navdata_t) << endl;
	cout << "checksum:" << sizeof(navdata_cks_t) << endl;
	cout << "option:" << sizeof(navdata_option_t) << endl;
	cout << sizeof(navdata_demo_t) << endl;
}