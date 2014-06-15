#include <ardrone/net/TcpClient.h>
#include <ardrone/os/win/inc.h>
using namespace whu;
//using namespace whu::ardrone;

class TcpClient::socket_impl {
private:
	SOCKET sck;
	sockaddr_in sckaddr;
	bool valid;
public:
	~socket_impl() {
		if (valid) {
			closesocket(sck);
		}
	}
	socket_impl(const char* ip,short port) {

	}
	bool send(const char* data, int len) {
		return true;
	}
	bool recv(char* data, int len, void(*callback)(void* param)) {
		return true;
	}
	bool is_valid() {
		return valid;
	}
};
// ------------------------------------------------------
TcpClient::~TcpClient() {
	if (sck_impl->is_valid()) {
		delete sck_impl;
		sck_impl = nullptr;
	}
}
TcpClient::TcpClient(const char* ip,short port) {
	valid = false;
	sck_impl = new socket_impl(ip, port);
	valid = sck_impl->is_valid();
}
bool TcpClient::is_valid() {
	return valid;
}
bool TcpClient::send(const char* data, int len) {
	return sck_impl->send(data, len);
}
bool TcpClient::recv(char* data, int len, void(*callback)(void* param)) {
	return sck_impl->recv(data, len, callback);
}