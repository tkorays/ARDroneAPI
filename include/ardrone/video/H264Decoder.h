#ifndef _TK_H264DECODER_H_
#define _TK_H264DECODER_H_
#include "../basic/type.h"

struct AVFormatContext;
struct AVCodecContext;
struct AVIOContext;
struct AVCodec;
struct AVFrame;
struct AVPacket;

namespace whu{
	class H264Decoder{
	private:
		AVFormatContext* pFormatCtx;
		AVCodecContext* pCodecCtx;
		AVIOContext* pIOCtx;
		AVCodec* pCodec;
		AVFrame* pFrame;
		AVFrame* pFrameYUV;
		void error_handle();
	public:
		H264Decoder();
		void process(void* data, int size, void(*callback)(void*p));
	};
}
#endif // _TK_H264DECODER_H_