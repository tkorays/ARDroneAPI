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
			uint16_t tag; /**< ��ǩ��id */
			uint16_t size; /**< ��С */
			byte_t data[1]; /**< ���� */
		} navdata_option_t;

		/**
		 * @brief һ��navigation�����ݽṹ,������У���
		 */
		typedef struct _navdata_t {
			uint32_t header; /**< ����ͷ */
			uint32_t ardrone_state; /**< ardrone��״̬��Ϣ */
			uint32_t sequence; /**< ���б�� */
			bool_t vision_defined; /**< �Ƿ�ʹ��vision */
			navdata_option_t options[1]; /**< ����ѡ�� */
		} navdata_t;

		/**
		 * @brief navdata demo���ݰ�
		 */
		typedef struct _navdata_demo_t {
			uint16_t tag; /**< ��ǩ��id�� */
			uint16_t size; /**< ��С */
			uint32_t ctrl_state; /**< control��״̬ */
			uint32_t vbat_flying_precentage; /**< ������ */

			float32_t theta; /**< theta�� */
			float32_t phi; /**< phi�� */
			float32_t psi; /**< psi */

			int32_t altitude; /**< �߶� */

			float32_t vx; /**< x�����ٶ� */
			float32_t vy; /**< y�����ٶ� */
			float32_t vz; /**< z�����ٶ� */

			uint32_t num_frames; /**< ��Ƶ֡�� */

			// some deprecated optons

		} navdata_demo_t;

		/**
		 * @brief navdata��У���
		 */
		typedef struct navdata_cks_t {
			uint16_t tag; /**< ��ǩ��id */
			uint16_t size; /**< ��С */
			uint32_t cks; /**< У������ */
		} navdata_cks_t;

	}
}
#endif // _TK_NAVDATA_COMMON_H_