#include <opencv2/opencv.hpp>
#include <cv_link_all.h>
using namespace cv;

#include <ardrone/ardrone.h>
#pragma comment(lib,"ARDrone.lib")
using namespace whu;
using namespace whu::ardrone;
using namespace std;

Mat img(360, 640, CV_8UC3);

void show(void* data){
	img.data = (uchar*)data;
	imshow("img", img);
	waitKey(33);
}

int main(){
	net_prepare();
	H264Decoder h264;
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
	void* frame_data = malloc(102400);
	int size=0;
	memset(frame_data, 0, 102400);
	VideoEncap encap;
	while (true) {
		videoClient->recv(buf, max_buf_size, NULL);
		//vardump_hex(buf, max_buf_size); // output the data (hex format)
		if (encap.process(buf)) {
			if (cnt%10 == 9){
				h264.process(frame_data, size, show);
				size = 0;
				memset(frame_data, 0, 102400);
				cnt++;
			}
			else{
				memcpy((char*)frame_data + size, encap.get_data(), encap.get_data_size());
				size += encap.get_data_size();
				cnt++;
			}
			
			//vardump_hex(encap.get_data(), encap.get_data_size());
		}
	}

	
	net_end();
	return 0;
}