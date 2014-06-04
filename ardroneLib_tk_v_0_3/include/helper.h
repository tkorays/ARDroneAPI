/**
 **************************************************************
 * Copyright tkorays(c),2013-2014
 * 
 * @file     helper.h
 * @brief    Helper function for net or transforming data 
 * @author   tkorays
 * @version  0.3
 * @date     2014/6/2
 **************************************************************
 */

#ifndef _TK_HELPER_
#define _TK_HELPER_
#pragma once

#include <string>
using namespace std;
#include "comdef.h"

/**
 * @brief auto link lib on windows if you defined macro "LIB_AUTO_LINK"
*/
#ifdef WIN32
#ifdef LIB_AUTO_LINK
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"iphlpapi.lib")
#endif
#endif

namespace tk {

	/**
	 * @fn f32_int32_adjust
	 * @brief float(32bit) to int32
	 * @param the input float number
	 * @return int32 number
	 */
	int f32_int32_adjust(const float);

	/**
	 * @brief prepare socket library on windows
	 */
	void net_prepare();

	/**
	 * @brief release ws2_32.dll library
	 */
	void net_end();

	/**
	* @brief get local ip on this PC
	*/
	string get_local_ip();

	/** 
	 * @brief check return status from functions 
	 * check status,but not handle mistakes.
	 * this function is used for showing mistakes when developing.
	 */
	void check_status(STATUS status,const string msg);

	/**
	* @brief Exit bootstrap mode if the status sent by ardrone indicates that the drone is in bootstrap mode.
	* @return return bool* actually
	*/
	void* bootstrap_check(void* param);

	void console_color_reset();

	/**
	 * @brief 0=��ɫ 1=��ɫ 2=��ɫ 3=����ɫ 4=��ɫ 5=��ɫ
     *        6=��ɫ 7=��ɫ 8=��ɫ 9=����ɫ A=����ɫ B=��ǳ��ɫ
     *        C=����ɫ D=����ɫ E=����ɫ F=����ɫ
	 */
	void console_color_set(unsigned short color);
}




#endif // _TK_HELPER_