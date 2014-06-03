#ifndef _TK_THREAD_HELPER_H_
#define _TK_THREAD_HELPER_H_
#pragma once

#include "comdef.h"
#include <Windows.h>

#define thread_dw_ret DWORD WINAPI

typedef HANDLE Thread_t;


/**
 * @brief impliment a no-return & no-param thread function table
 */

#define __CLAIM_THREAD_TABLE__ void THREAD_TABLE_EXEC();
#define THREAD_TABLE_START(thread_num) void THREAD_TABLE_EXEC(){\
	int t_num = (thread_num); \
	Thread_t _thread_table[(thread_num)]; \
	DWORD _thread_id[(thread_num)]; \
	int count = 0;

#define CREATE_THREAD(func) if(count>=t_num){;}else{\
	_thread_table[count] = \
	CreateThread(NULL, 0, func, NULL, TRUE, (_thread_id + count)); \
	count++; }

#define THREAD_TABLE_END WaitForMultipleObjects(t_num,_thread_table,TRUE,INF); \
	return; }



#endif // _TK_THREAD_HELPER_H_