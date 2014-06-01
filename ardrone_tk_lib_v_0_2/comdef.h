#ifndef _TK_COMDEF_H_
#define _TK_COMDEF_H_
#pragma once
#define LF_DEF '\x0a' // <LF>
#define CR_DEF '\x0d' // <CR>

#define ARDRONE_IP "192.168.1.1"


#define TAKEOFF_CODE 0x11540200
#define LAND_CODE    0x11540000
#define EMERG_CODE   0x11540100


#define FTP_PORT	         5551
#define AUTH_PORT            5552
#define VIDEO_RECORDER_PORT  5553
#define NAVDATA_PORT         5554
#define VIDEO_PORT           5555
#define AT_PORT              5556
#define RAW_CAPTURE_PORT     5557
#define PRINTF_PORT          5558
#define CONTROL_PORT         5559

typedef int TK_STATUS;
#define TK_OK                1
#define TK_FAILED           -1
#define TK_ERROR            -2

#define TK_SOCK_ERROR         50
#define TK_


#endif // _TK_COMDEF_H_