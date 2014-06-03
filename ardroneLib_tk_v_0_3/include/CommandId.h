/**
**************************************************************
* Copyright tkorays(c),2013-2014
*
* @file     CommandId.h
* @brief    manage the AT command id number
* @author   tkorays
* @version  0.3
* @date     2014/6/2
**************************************************************
*/

#ifndef _TK_COMMAND_ID_H_
#define _TK_COMMAND_ID_H_
#pragma once
#include "Mutex.h"
#include "comdef.h"

namespace tk {
	/**
	 * @brief manage AT command id number
	 *  auto-increment,ensure all the AT command have their own id
	 */
	class CommandId {
	private:
		long id; // the auto-increment number
		Mutex id_mutex;
	public:
		CommandId(); // init id = -1
		~CommandId();
		void inc(); // inc 
		void operator++(); // inc operator
		void reset(); // reset id to -1
		/*
		 * @brief get command id of itself
		 * @param id auto_inc when "auto_inc" is true
		 */
		long get_id(bool auto_inc=true);
		bool mutex_wait(unsigned long wait_time);
		bool mutex_unlock();
		bool mutex_release();
	};
}

#endif // _TK_COMMAND_ID_H_