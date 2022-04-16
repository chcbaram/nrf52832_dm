/*
 * hw.c
 *
 *  Created on: Dec 6, 2020
 *      Author: baram
 */


#include "hw.h"



void hwInit(void)
{
  uint32_t pre_time;
  uint32_t exe_time;

  pre_time = millis();
  bspInit();

  logInit();
  cliInit();
  resetInit();
  ledInit();
  buttonInit();
  uartInit();
  uartOpen(_DEF_UART1, 115200);

  logPrintf("\n");
  logPrintf("[ Firmware Begin... ]\r\n");
  resetLog();

  exe_time = millis()-pre_time;

  logPrintf("boot time \t: %d ms\r\n", exe_time);
}

