/*
 * startup.h
 *
 *  Created on: Nov 15, 2016
 *      Author: RoyerAriel
 */

#ifndef STARTUP_C_
#define STARTUP_C_

#include "SysTimer.h"
#include "define.h"

void startup()
{

  //Start Systick Timer at 1ms
  Systick_Startup();
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE; //0x‭2000000‬ disable JTAG
}

#endif  /* STARTUP_C_ */
