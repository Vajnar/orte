/*
 *  $Id: orte_headers.h,v 0.0.0.1       2003/08/21 
 *
 *  AUTHOR: Petr Smolik                 petr.smolik@wo.cz
 *
 *  ORTE - OCERA Real-Time Ethernet     http://www.ocera.org/
 *  --------------------------------------------------------------------
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 */

#ifndef _ORTE_ALL_H
#define _ORTE_ALL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_CONFIG_H
  #include "orte_config.h"
#elif defined OMK_FOR_USER
  #include "orte_config_omk_unix.h"
#elif defined OMK_FOR_KERNEL
  #include "orte_config_omk_rtl.h"
#endif

#ifdef HAVE_ARPA_INET_H
  #include <arpa/inet.h>
#endif
#ifdef HAVE_FCNTL_H
  #include <fcntl.h>
#endif
#ifdef HAVE_STDIO_H
  #include <stdio.h>
#endif
#ifdef HAVE_NETDB_H
  #include <netdb.h>
#endif
#ifdef HAVE_STDLIB_H
  #include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
  #include <string.h>
#endif
#ifdef HAVE_SYS_IOCTL_H
  #include <sys/ioctl.h>
#endif
#ifdef HAVE_SYS_TIME_H
  #include <sys/time.h>
#endif
#ifdef HAVE_UNISTD_H
  #include <unistd.h>
#endif
#ifdef HAVE_PTHREAD_H
  #include <pthread.h>
#endif
#ifdef HAVE_SYS_TYPES_H
  #include <sys/types.h>
#endif
#ifdef HAVE_SYS_SOCKIO_H
  #include <sys/sockio.h>
#endif
#ifdef HAVE_STDARG_H
  #include <stdarg.h>
#endif
#ifdef HAVE_BYTESWAP_H
  #include <byteswap.h>
#endif
#ifdef HAVE_GETOPT_H
  #include <getopt.h>
#endif
#ifdef HAVE_CTYPE_H
  #include <ctype.h>
#endif
#ifdef HAVE_SIGNAL_H
  #include <signal.h>
#endif
#ifdef HAVE_STDINT_H
  #include <stdint.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
  #include <sys/socket.h>
#endif
#ifdef HAVE_NETINET_IN_H
  #include <netinet/in.h>
#endif
#ifdef HAVE_NET_IF_H
  #include <net/if.h>
#endif
#ifdef HAVE_ERRNO_H
  #include <errno.h>
#endif
//win32 headers
#if defined HAVE_WINSOCK2_H && !HAVE_SYS_SOCKET_H
  #include <winsock2.h>
#endif
#if defined HAVE_WS2TCPIP_H && !HAVE_SYS_SOCKET_H
  #include <ws2tcpip.h>
#endif
#ifdef HAVE_WINDOWS_H
  #include <windows.h>
#endif
#ifdef HAVE_W32API_WINDOWS_H
  #include <w32api/windows.h>
#endif
#ifdef HAVE_ERRNO_H
  #include <errno.h>
#endif
//kernel headers
#ifdef HAVE_ASM_BYTEORDER_H
  #include <asm/byteorder.h>
#endif
#ifdef HAVE_LINUX_CTYPE_H
  #include <linux/ctype.h>
#endif
#ifdef HAVE_LINUX_STRING_H
  #include <linux/string.h>
#endif
#ifdef HAVE_LINUX_MODULE_H
  #include <linux/module.h>
#endif
#ifdef HAVE_LINUX_IF_H
  #include <linux/if.h>
#endif
#ifdef HAVE_LINUX_SOCKET_H
  #include <linux/socket.h>
#endif
#ifdef HAVE_LINUX_TIME_H
  #include <linux/time.h>
#endif
#ifdef HAVE_LINUX_TYPES_H
  #include <linux/types.h>
#endif
#ifdef HAVE_LINUX_IN_H
  #include <linux/in.h>
#endif
//RTL headers
#ifdef HAVE_RTL_H
  #include <rtl.h>
#endif
#ifdef HAVE_RTL_MALLOC_H
  #include <rtl_malloc.h>
#endif
#ifdef HAVE_UDP_H
  #include <udp.h>
#endif
#ifdef HAVE_NIC_H
  #include <nic.h>
#endif
#ifdef HAVE_NICTAB_H
  #include <nictab.h>
#endif
#ifdef HAVE_TIME_H
  #include <time.h>
#endif
//RTAI headers
#ifdef HAVE_RTNET_H
  #include <rtnet.h>
#endif

#ifdef CONFIG_ORTE_UNIX
  #define SOCK_BSD       
#elif CONFIG_ORTE_CYGWIN
  #define SOCK_BSD         
#elif CONFIG_ORTE_MINGW
  #define SOCK_WIN
  #include <win32/pthread.h>
  #include <win32/timeval.h>
  #ifndef __GETOPT_H__  //mingw
    #include <win32/getopt.h>
  #endif
  #include <orte/ew_types.h>
  #define ioctl ioctlsocket
#elif defined CONFIG_ORTE_RTL
  #define SOCK_RTL
  #include <rtl/compat.h>
  #include <rtl/rwlock.h>
#elif defined CONFIG_ORTE_RTAI
  #define SOCK_BSD  
  #include <rtai/compat.h>
#elif defined _MSC_VER
  #define SOCK_WIN
  #ifndef inline
    #define inline _inline
  #endif
  #include <stdio.h>
  #include <stdlib.h>
  #include <stdarg.h>
  #include <string.h>
  #include <winsock2.h>
  #include <ws2tcpip.h>
  #include <windows.h>
  #include <win32/pthread.h>
  #include <win32/timeval.h>
  #include <win32/getopt.h>
  #include <orte/ew_types.h>
  #define ioctl ioctlsocket
  #define ORTE_PACKAGE_STRING "orte 0.2.3"
  #define CONFIG_ORTE_WIN
#endif

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif /* _ORTE_ALL_H */
