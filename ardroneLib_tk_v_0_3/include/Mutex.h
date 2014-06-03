/**
**************************************************************
* Copyright tkorays(c),2013-2014
*
* @file     CommandId.h
* @brief    multi threads sync
* @author   tkorays
* @version  0.3
* @date     2014/6/3
**************************************************************
*/
#ifndef _TK_MUTEX_H_
#define _TK_MUTEX_H_
#pragma once

#include <Windows.h>

namespace tk {
	/** 
	 * @brief Use mutex_t instead of original HANDLE.
	 */
	typedef HANDLE mutex_t;
	/**
	 * @brief MultiThreads sync
	 */
	class Mutex {
	private:
		mutex_t mutex;
	public:
		Mutex();
		/**
		 * @brief wait until other threads release mutex
		 * @param wait-time
		 */
		bool wait(unsigned long wait_time);
		/**
		 * @brief release mutex
		 */
		bool unlock();
	};
}


#endif // _TK_MUTEX_H_