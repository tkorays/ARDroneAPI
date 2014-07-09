#include <ardrone/video/H264Decoder.h>
extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libswscale/swscale.h>
#include <libavutil/file.h>
}
#include <Windows.h>
using namespace whu;


static int read_packet(void *opaque, uint8_t *buf, int buf_size)
{
	struct buffer_data *bd = (struct buffer_data *)opaque;
	memset(buf, 0, buf_size);
	buf_size = FFMIN(buf_size, bd->size);
	memcpy(buf, bd->ptr, buf_size);
	bd->ptr += buf_size;
	bd->size -= buf_size;
	return buf_size;
}

H264Decoder::H264Decoder(){
	// init basic var 
	pFormatCtx = NULL;
	pIOCtx = NULL;
	buffer = NULL;
	avio_ctx_buffer = NULL;
	avio_ctx_buffer_size = 640*360;
	bd = { 0 };

	av_register_all(); // 注册所有组件
	// 分配avio的缓存
	avio_ctx_buffer = (uint8_t*)av_malloc(avio_ctx_buffer_size);
	if (!avio_ctx_buffer){
		valid = false;
		return;
	}
	
	// 初始化FormatContext
	pFormatCtx = avformat_alloc_context();
	if (!pFormatCtx){
		valid = false;
		return;
	}
	pCodec = avcodec_find_decoder(AV_CODEC_ID_H264);
	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();
	valid = true;
	isOpen = false;
	pIOCtx = avio_alloc_context(avio_ctx_buffer, avio_ctx_buffer_size, 0, &bd, &read_packet, NULL, NULL);
	pFormatCtx->pb = pIOCtx;

}
void H264Decoder::process(void* data, int size, void(*callback)(void*p)){
	bd.ptr = (uint8_t*)data;
	bd.size = size;
	
	int ret;
	if (!isOpen)
	{
		ret = avformat_open_input(&pFormatCtx, NULL, NULL, NULL);
		if (ret<0){
			return;
		}
		
		ret = avformat_find_stream_info(pFormatCtx, NULL);
		if (ret<0){
			return;
		}
		pCodecCtx = pFormatCtx->streams[0]->codec;
		if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
			printf("could not open codec\n");
		}
		if (pCodec->capabilities&CODEC_CAP_TRUNCATED) {
			pCodecCtx->flags |= CODEC_FLAG_TRUNCATED;
		}
		out_buffer = new uint8_t[avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height)];
		packet = (AVPacket*)malloc(sizeof(AVPacket));
		av_new_packet(packet, pCodecCtx->width*pCodecCtx->height);
		avpicture_fill((AVPicture *)pFrameYUV, out_buffer, PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);

		isOpen = true;
	}
	
	//av_dump_format(pFormatCtx, 0, "", 0);
	//Sleep(40);
	
	static struct SwsContext *img_convert_ctx;
	int got_picture;
	while (av_read_frame(pFormatCtx, packet) >= 0)
	{
		//printf("packet id:%d\n", packet->stream_index); 
		if (packet->stream_index!=0)
		{
			return;
		}
		int len = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
		if (len < 0) {
			return;
		}
		//printf("got frame:%d\n", got_picture);
		if (got_picture) {
			img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);
			sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
			sws_freeContext(img_convert_ctx);
			if (callback){
				callback((pFrameYUV->data[0]));

			}
		}
		
	}
	//delete out_buffer;
	//free(packet);
	//av_free(pIOCtx);
}
bool H264Decoder::is_ok(){
	return valid;
}

H264Decoder::~H264Decoder(){
	avformat_close_input(&pFormatCtx);
	av_free(pFormatCtx);
	av_free(pCodecCtx);
	av_free(pIOCtx);
	delete out_buffer;
	free(packet);
}