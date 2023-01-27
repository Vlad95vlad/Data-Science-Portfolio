
#ifndef APP_DEBUG_H
#define APP_DEBUG_H

#include "stm32h753xx.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_it.h"
#include "task.h"
#include "debug.h"
#include "Cyclone_TCP/cyclone_tcp/core/net.h"

#define TASK_COUNT   10

// definition commands word
#define _CMD_HELP   "help"
#define _CMD_CLEAR  "clear"
#define _CMD_MON    "monitor"
#define _CMD_GET    "get"
#define _CMD_SET    "set"
#define _CMD_READ   "read_exflash"
#define _CMD_SAVE   "save"


// arguments for set/clear
	#define _SCMD_GTW   "gateway"
	#define _SCMD_IP    "ip"
	#define _SCMD_MAC   "mac"
	#define _SCMD_MASK  "netmask"
	#define _SCMD_PROT  "protocol"
	#define _SCMD_PASSW "password"		// установка пароля

#define _NUM_OF_CMD 7
#define _NUM_OF_SETCLEAR_SCMD 6

typedef struct header
{
	uint8_t SOM;
	uint8_t com;
	uint8_t len;
	uint16_t crc;

} header_t;

void vConfigureTimerForRunTimeStats( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vMonitorTask( void *pvParametrs);
	void Monitor(void);
	uint8_t _task_state_to_char(eTaskState taskstate);

void vMrlTask ( void *pvParametrs );
	int execute (int argc, const char * const * argv);
	char ** complet (int argc, const char * const * argv);
	void sigint (void);
	void putc_for_mrl(const char* fmt);
	char mrl_get_char (void);
	void help(void);
	uint8_t check_digit(const char* fmt);

void vUDPTask( void *pvParametrs );

#endif /*APP_DEBUG_H */

