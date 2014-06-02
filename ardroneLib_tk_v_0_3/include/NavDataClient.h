/**
**************************************************************
* Copyright tkorays(c),2013-2014
*
* @file     NavDataClient.h
* @brief    manage navdata
* @author   tkorays
* @version  0.3
* @date     2014/6/2
**************************************************************
*/

#ifndef _TK_NAVDATA_CLIENT_H_
#define _TK_NAVDATA_CLIENT_H_
#pragma once

#include "ATCmdGenerator.h"
#include "ATCmdClient.h"
#include "basic_struct.h"
#include "comdef.h"
#include <WinSock2.h>

namespace tk {
	/**
	 * @brief manage navdata
	 * sometimes dispatch it's job to ATCmdClient,e.g. send AT commands
	 * The main function is reveiving data and executing the callback function when recieving data.
	 */
	class NavDataClient {
	private:
		bool bootstrap_mod; // flag for bootstrap mode
		SOCKET nav_sck; // socket for navdata,UDP-5554
		sockaddr_in nav_sck_addr; // nav_sck_addr
		bool nav_sck_running; // flag for save the socket status. When socket is aviable, nav_sck_running is true.
		bool wait_and_recv;
		ATCmdGenerator* cmd_gen;
		ATCmdClient* at_cmd_client;

		STATUS init_socket();
		STATUS send_data(const char* dt,int len);
	public:
		NavDataClient(ATCmdGenerator* gen,ATCmdClient* client); // set nav_sck_running
		/**
		 * @brief init navdata client
		 */
		STATUS init_navdata_client(); 
		/**
		* @brief release socket and so on. Call this function when you don't want receive navdata.
		*/
		STATUS release_navdata_client(); 
		/** 
		 * @brief receive data. When package is reached, execute the callback function.
		 */
		STATUS recv_pack(char* data,int len,void* (*callback)(void*param)); 
		/** 
		 * @brief dispatch At command to ATCmdClient
		 */
		STATUS dispatch_at_cmd(at_cmd cmd);
	};
	/**
	 * @brief Exit bootstrap mode if the status sent by ardrone indicates that the drone is in bootstrap mode.
	 * @return return bool* actually
	 */
	void* bootstrap_check(void* param);
}
#endif // _TK_NAVDATA_CLIENT_H_