#ifndef _TK_NAVDATA_COMMON_H_
#define _TK_NAVDATA_COMMON_H_

#include "navdata_tag.h"
#include "../basic/type.h"
using namespace whu;

#define NAVDATA_HEADER 0X55667788
#define NAVDATA_MAX_SIZE 4096


#define NAVDATA_OPTION_MASK(option) (1<<(option))
#define NAVDATA_OPTION_FULL_MASK ((1<<NAVDATA_NUM_TAGS)-1)
namespace whu {
	namespace ardrone {
		/**
		 * @brief navdata option
		 */
		typedef struct _navdata_option_t {
			uint16_t tag; /**< 标签，id */
			uint16_t size; /**< 大小 */
			byte_t data[1]; /**< 数据 */
		} navdata_option_t;

		/**
		 * @brief 一条navigation的数据结构,不包含校验和
		 */
		typedef struct _navdata_t {
			uint32_t header; /**< 数据头 */
			uint32_t ardrone_state; /**< ardrone的状态信息 */
			uint32_t sequence; /**< 序列编号 */
			bool_t vision_defined; /**< 是否使用vision */
			navdata_option_t options[1]; /**< 各种选项 */
		} navdata_t;

		/**
		 * @brief navdata demo数据包
		 */
		typedef struct _navdata_demo_t {
			uint16_t tag; /**< 标签（id） */
			uint16_t size; /**< 大小 */
			uint32_t ctrl_state; /**< control的状态 */
			uint32_t vbat_flying_precentage; /**< 。。。 */

			float32_t theta; /**< theta角 */
			float32_t phi; /**< phi角 */
			float32_t psi; /**< psi */

			int32_t altitude; /**< 高度 */

			float32_t vx; /**< x方向速度 */
			float32_t vy; /**< y方向速度 */
			float32_t vz; /**< z方向速度 */

			uint32_t num_frames; /**< 视频帧数 */

			// some deprecated optons

		} navdata_demo_t;

		/**
		 * @brief navdata的校验和
		 */
		typedef struct navdata_cks_t {
			uint16_t tag; /**< 标签，id */
			uint16_t size; /**< 大小 */
			uint32_t cks; /**< 校验数据 */
		} navdata_cks_t;

	}
}
#endif // _TK_NAVDATA_COMMON_H_