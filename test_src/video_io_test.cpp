#include <opencv2/opencv.hpp>
#include <cv_link_all.h>
using namespace cv;

#include <ardrone/ardrone.h>
#pragma comment(lib,"ARDrone.lib")
using namespace whu;
using namespace whu::ardrone;
using namespace std;

Mat img(360, 640, CV_8UC3);
H264Decoder h264;
VideoEncap encap;
whu::Mutex mutex;
void show(void* data){
	img.data = (uchar*)data;
	imshow("img", img);
	waitKey(33);
}
DWORD WINAPI h264_show(void*){
	while (true)
	{
		mutex.lock(100);
		h264.process(encap.get_data(), encap.get_data_size(), show);
		mutex.unlock();
	}
	
	return 0;
}
int main(){
	net_prepare();
	namedWindow("img");
	if (!h264.is_ok()){
		cout << "h264 error!" << endl;
		abort();
	}
	int cnt = 0;
	// Connect the AR.Drone video port
	TcpClient* videoClient = new  TcpClient(ARDRONE_IP, VIDEO_PORT);
	if (!videoClient->is_valid()) {
		cerr << "can't connnected to the video tcp..." << endl;
		abort();
	}
	const int max_buf_size = VideoEncap::TcpPackSize;
	char* buf = (char*)malloc(max_buf_size);
	
	//DWORD tid;
	//HANDLE hShow = CreateThread(NULL, 0, h264_show, NULL, 0, &tid);

	while (true) {
		videoClient->recv(buf, max_buf_size, NULL);
		//vardump_hex(buf, max_buf_size); // output the data (hex format)
		if (encap.process(buf)) {
			h264.process(encap.get_data(), encap.get_data_size(), show);
			
			//vardump_hex(encap.get_data(), encap.get_data_size());
		}
	}

	
	net_end();
	return 0;
}