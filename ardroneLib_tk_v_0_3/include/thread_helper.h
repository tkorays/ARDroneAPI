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
#define THREAD_TABLE_START(thread_num) void THREAD_TABLE_EXEC(){\
	Thread_t _thread_table[thread_num]; \
	DWORD _thread_id[thread_num];

#define THREAD(num,func) _thread_table[num] = \
	CreateThread(NULL, 0, func, NULL, TRUE, _thread_id[num]);

#define THREAD_TABLE_END WaitForMultipleObjects(thread_num,_thread_table,TRUE,INF); \
	return; }



#endif // _TK_THREAD_HELPER_H_