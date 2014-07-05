/**
 * @file video_getdata.h
 * @ brief ��tcp���л�ȡԭʼ��Ƶ����
 * 
 * @author tkorays
 * @date 2014-6-20
 * @since 1.0.0
 *
 * ԭʼ����Ƶ֡�ֲ��ڲ�ͬ�����ݰ��У������Ҫ��������Ѽ�������
 */

#ifndef _TK_VIDEO_GETDATA_H_
#define _TK_VIDEO_GETDATA_H_

namespace whu {
	namespace ardrone {
		/**
		 * @class VideoEncap VideoEncap.h ardrone/video/VideoEncap.h
		 * @brief ������Ƶ���
		 */
		class VideoEncap {
		private:
			void* data; // �õ�����Ƶ����
			int data_index; // ��ǰ��Ƶ�ڲ��������������ڸ�������
			int data_size;
			bool data_over;
		public:
			VideoEncap();
			/*!< tcp���Ĵ�С */
			static int TcpPackSize; 
			/**
			 * @brief ����tcp����
			 * @param ԭʼtcp����
			 * @return �������
			 */
			bool process(void* tcpdata);
			int get_data_size();
			void* get_data();
		};
	}
}

#endif // _TK_VIDEO_GETDATA_H_