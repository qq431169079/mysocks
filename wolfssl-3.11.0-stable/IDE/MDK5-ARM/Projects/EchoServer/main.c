/* main.c
 *
 * Copyright (C) 2006-2016 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */
 
#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolfssl/wolfcrypt/visibility.h>
#include <wolfssl/wolfcrypt/logging.h>

#include "stm32f2xx_hal.h"
#include "cmsis_os.h"
#include "rl_net.h" 
#include <stdio.h>

#include <wolfssl/ssl.h>

/*-----------------------------------------------------------------------------
 *        Initialize Clock Configuration
 *----------------------------------------------------------------------------*/
void SystemClock_Config(void) {
    #warning "write MPU specific System Clock Set up\n"
}

/*-----------------------------------------------------------------------------
 *        Initialize a Flash Memory Card
 *----------------------------------------------------------------------------*/
 #if !defined(NO_FILESYSTEM)
#include "rl_fs.h"
static void init_filesystem (void) {
  int32_t retv;

  retv = finit ("M0:");
  if (retv == 0) {
    retv = fmount ("M0:");
    if (retv == 0) {
      printf ("Drive M0 ready!\n");
    }
    else {
      printf ("Drive M0 mount failed!\n");
    }
  }
  else {
    printf ("Drive M0 initialization failed!\n");
  }
}
#endif


/*-----------------------------------------------------------------------------
 *       mian entry 
 *----------------------------------------------------------------------------*/

typedef struct func_args {
    int    argc;
    char** argv;
} func_args;

extern void echoserver_test(func_args * args) ;

int main() 
{
    func_args args ;
		args.argc = 1 ;

    SystemClock_Config ();
    #if !defined(NO_FILESYSTEM)
    init_filesystem ();
    #endif
    netInitialize() ;
    osDelay(300) ;  
    #if defined(DEBUG_WOLFSSL)
         printf("Turning ON Debug message\n") ;
         wolfSSL_Debugging_ON() ;
    #endif
        printf("echoserver: Started\n") ;
    echoserver_test(&args) ;
    printf("echoserver: Terminated\n") ;
}
