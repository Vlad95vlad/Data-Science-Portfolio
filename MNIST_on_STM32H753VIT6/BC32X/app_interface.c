
#include <app_interface.h>
#include "app_periph.h"
#include "app_enet.h"
#include "microrl.h"
#include "crc16tab.h"
#include "neural_network.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

extern app_periph_t app_periph;
extern app_os_resources_t app_os_res;
extern HttpServerSettings httpServerSettings;
extern app_enet_t * apEnParam;

//available  commands
char * keyworld [] = {_CMD_HELP, _CMD_CLEAR, _CMD_MON, _CMD_GET, _CMD_SET, _CMD_READ, _CMD_SAVE};
// 'set/clear' command argements
char * set_clear_key [] = {_SCMD_GTW, _SCMD_IP, _SCMD_MAC, _SCMD_MASK, _SCMD_PROT, _SCMD_PASSW};
// array for comletion
char * compl_world [_NUM_OF_CMD + 1];



void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	/* This function will get called if a task overflows its stack. */

	( void ) pxTask;
	( void ) pcTaskName;

	TRACE_INFO("Stack overflow in %s task\n", pcTaskName);

	for( ;; )
	{
		for(uint32_t i = 0; i != 0xffffffff; i++);
			TRACE_INFO("Stack overflow in %s task\n", pcTaskName);
	}
}


void vMonitorTask( void *pvParametrs)
{
	for(;;)
	{

		Monitor( );
		vTaskDelay( 10000 );
	}
}

void Monitor(void)
{
	UBaseType_t task_count = uxTaskGetNumberOfTasks();

	if (task_count <= TASK_COUNT)
	{
		unsigned long _total_runtime;
		TaskStatus_t _buffer[TASK_COUNT];

		task_count = uxTaskGetSystemState(_buffer, task_count, &_total_runtime);

		TRACE_INFO("\r\n[DEBG] %20s %10s %10s %10s %10s\r\n", "tName", "tState", "tPriority",  "tFreeStack", "tTotalTime");

		for (int task = 0; task < task_count; task++)
		{
			TRACE_INFO("[DEBG] %20s:      %c, %8u, %8u, %10u ms\r\n",
						_buffer[task].pcTaskName,
						_task_state_to_char(_buffer[task].eCurrentState),
						_buffer[task].uxCurrentPriority,
						_buffer[task].usStackHighWaterMark,
						_buffer[task].ulRunTimeCounter / 100);
		}

		TRACE_INFO("[DEBG] Current Heap Free Size: %u\r\n", xPortGetFreeHeapSize());

		TRACE_INFO("[DEBG] Minimal Heap Free Size: %u\r\n", xPortGetMinimumEverFreeHeapSize());

		TRACE_INFO("[DEBG] Total RunTime:  %u ms\r\n", _total_runtime / 100);

		TRACE_INFO("[DEBG] System Uptime:  %u ms\r\n\r\n", xTaskGetTickCount() * portTICK_PERIOD_MS);
	 }
}

uint8_t _task_state_to_char(eTaskState taskstate)
{
	uint8_t state;

     switch(taskstate)
     {
		 case eRunning:     state = 'r';
							break;
		 case eReady:       state = 'R';
							break;
		 case eBlocked:     state = 'B';
							break;
		 case eSuspended:   state = 'S';
							break;
		 case eDeleted:     state = 'D';
							break;
		 case eInvalid:     state = 'I';
							break;
     }

	return state;
}

int _write (int fd, const char *ptr, int len)
{
	xSemaphoreTake( app_os_res.uart1_mutex, portMAX_DELAY );

    HAL_UART_Transmit(app_periph.huart1, ptr, len, 0xFFFF);

    if( apEnParam->clientTerminalTCPSocket->state != TCP_STATE_CLOSED &&
        apEnParam->clientTerminalTCPSocket->state != TCP_STATE_CLOSE_WAIT)
    	socketSend(apEnParam->clientTerminalTCPSocket, ptr, len, NULL, SOCKET_FLAG_BREAK_CRLF);

    xSemaphoreGive( app_os_res.uart1_mutex );

    return len;
}

int _read (int fd, char *ptr, int len)
{
    *ptr = 0x00; // Flush the character buffer

    if ( uxQueueMessagesWaiting( app_os_res.xQueueRX_TCP_MRL ) != 0 )
	{
		portBASE_TYPE xStatus = xQueueReceive( app_os_res.xQueueRX_TCP_MRL, ptr, 0 );            // читаем из очереди

		if( xStatus == pdPASS )
			return 1;
	}
    HAL_UART_Receive(app_periph.huart1, (uint8_t*) ptr, 1, 0x0);

    return 1;
}

void vMrlTask ( void *pvParametrs )
{
	// Создаем microrl объект и указатель на него
	microrl_t rl;
	microrl_t * prl = &rl;

    microrl_init (prl, putc_for_mrl);             //  которая будет выводить сообщения в терминал
	microrl_set_execute_callback (prl, execute);  // устанавливаем вызов для execute
	microrl_set_complete_callback (prl, complet);
	microrl_set_sigint_callback (prl, sigint);    // устанавливаем вызов для ctrl+c обработки (опционально)

	for(;;)
	{
		microrl_insert_char (prl, mrl_get_char());
	}
}

//*****************************************************************************
// execute callback for microrl library
// do what you want here, but don't write to argv!!! read only!!
int execute (int argc, const char * const * argv)
{
	int i = 0;
	// just iterate through argv word and compare it with your commands
	while (i < argc)
	{
		if (strcmp (argv[i], _CMD_HELP) == 0)
		{
			help();
		}
		else if (strcmp (argv[i], _CMD_CLEAR) == 0)
		{
			TRACE_INFO("\033[2J");    // ESC seq for clear entire screen
			TRACE_INFO("\033[H");     // ESC seq for move cursor at left-top corner
		}
		else if (strcmp (argv[i], _CMD_MON) == 0)
		{
			Monitor( );
		}
		else if (strcmp (argv[i], _CMD_SAVE) == 0)
		{
			//SavetoFlashCrc(0x000F0000, (uint8_t *) apEnParam->EnetParam, sizeof(Enet_Param_t), TRUE);
		}
		else if (strcmp (argv[i], _CMD_GET) == 0)
		{
			TRACE_INFO("MAC addr: %s\n\r",      apEnParam->EnetParam->myMAC);
			TRACE_INFO("IP addr: %s\n\r",       apEnParam->EnetParam->myIP);
			TRACE_INFO("Net mask: %s\n\r",      apEnParam->EnetParam->myMASK);
			TRACE_INFO("Gateway addr: %s\n\r",  apEnParam->EnetParam->myGTW);
			TRACE_INFO("Protocol type: %s\n\r", apEnParam->EnetParam->Http == HTTPS_PORT ? "HTTPS" :
	  	  	  	  	  	  	  	  	  	  	    (apEnParam->EnetParam->Http == HTTP_PORT ? "HTTP" : "Error"));
		}
		else if (strcmp (argv[i], _CMD_SET) == 0)
		{
			if (++i < argc)
			{
				uint8_t flag = 0;

				if (strcmp (argv[i], _SCMD_MAC) == 0)
				{
					if (++i < argc)
					{
						MacAddr macAddrNew;
						error_t error = macStringToAddr(argv[i], &macAddrNew);
						if (error)
						{
							TRACE_INFO("Invalid MAC.\n\r");
							return 1;
						}
						memcpy(apEnParam->EnetParam->myMAC, argv[i], 18);
						flag = 1;
					}
				}
				else if (strcmp (argv[i], _SCMD_MASK) == 0)
				{
					if (++i < argc)
					{
						Ipv4Addr ipv4Addrnew;
						error_t error = ipv4StringToAddr(argv[i], &ipv4Addrnew);
						if (error)
						{
							TRACE_INFO("Invalid subnet mask.\n\r");
							return 1;
						}
						memcpy(apEnParam->EnetParam->myMASK, argv[i], 16);
						flag = 1;
					}
				}
				else if (strcmp (argv[i], _SCMD_IP) == 0)
				{
					if (++i < argc)
					{
						Ipv4Addr ipv4Addrnew;
						error_t error = ipv4StringToAddr(argv[i], &ipv4Addrnew);
						if (error)
						{
							TRACE_INFO("Invalid IP.\n\r");
							return 1;
						}
						memcpy(apEnParam->EnetParam->myIP, argv[i], 16);
						flag = 1;
					}
				}
				else if (strcmp (argv[i], _SCMD_GTW) == 0)
				{
					if (++i < argc)
					{
						Ipv4Addr ipv4Addrnew;
						error_t error = ipv4StringToAddr(argv[i], &ipv4Addrnew);
						if (error)
						{
							TRACE_INFO("Invalid gateway address.\n\r");
							return 1;
						}
						memcpy(apEnParam->EnetParam->myGTW, argv[i], 16);
						flag = 1;
					}
				}
				else if (strcmp (argv[i], _SCMD_PASSW) == 0)
				{
					if (++i < argc)
					{
						uint8_t len_passw = strlen(argv[i]);
						if (len_passw > 8 || len_passw < 1)
						{
							TRACE_INFO("Password must be from 1 to 8 symbols.\n\r");
							return 1;
						}
						memcpy(apEnParam->EnetParam->myPassword, argv[i], 9);
						flag = 2;
					}
				}
				else if (strcmp (argv[i], _SCMD_PROT) == 0)
				{
					if (++i < argc)
					{
						if (!strcmp (argv[i], "https"))
						{
							apEnParam->EnetParam->Http = HTTPS_PORT;
							flag = 1;
						}
						else if (!strcmp (argv[i], "http"))
						{
							apEnParam->EnetParam->Http = HTTP_PORT;
							flag = 1;
						}
						else
							TRACE_INFO("Unknown protocol. Use https or http.\r\n");
					}
				}
				if(flag)
				{
					//SavetoFlashCrc(0x000F0000, (uint8_t *) apEnParam->EnetParam, sizeof(Enet_Param_t), TRUE);

					if(flag == 1)
					{
						SetNewNetConfig(apEnParam->EnetParam);
						//httpServerSettings.port = apEnParam->EnetParam->Http;
					}
				}
			}
		}
		else if (strcmp (argv[i], _CMD_READ) == 0)
		{
			if (++i < argc)
			{
				//uint32_t addr = atoi(argv[i]);
				uint32_t addr = strtol(argv[i], NULL, 16);

				if (addr <= 0xFEFFF && addr >= 0)
				{
					if (++i < argc)
					{
						uint32_t size = atoi(argv[i]);
						if(size <= 131072 && size > 0)
						{
							if( (addr + size) <= 0xfefff)
							{
								uint8_t * exflashbuf = (uint8_t *) osAllocMem( sizeof(uint8_t) * size );
								taskENTER_CRITICAL();
								//ReadM25_Buf(addr, exflashbuf, size);
								TRACE_INFO("Addr start: %#x, addr end: %#x, size: %u.\n\r", addr, addr + size, size);
								for(uint32_t i = 0; i < size; i += 16)
								{
									for(uint8_t j = 0; j < 16 && (i + j) < size; j++)
									{
										if(exflashbuf[i + j] >= 0x00 && exflashbuf[i + j] <= 0x0f)
											TRACE_INFO("0x0%u   ", exflashbuf[i + j]);
										else
											TRACE_INFO("%#x   ", exflashbuf[i + j]);
									}
									TRACE_INFO("\r\n");
								}
								taskEXIT_CRITICAL();
								osFreeMem(exflashbuf);
							}
							else
								TRACE_INFO("Addr + size is out of range.\n\r");
						}
						else
							TRACE_INFO("Size must be from 1 to 131072.\r\n");
					}
					else
						TRACE_INFO("Specify size.\n\r");
				}
				else
					TRACE_INFO("Addr must be from 0x000000 to 0x0fefff(16 sector 239 page 255 byte).\n\r");
			}
			else
				TRACE_INFO("Specify address(hex) and size (from 1 to 2048).\n\r");
		}
		else
		{
			TRACE_INFO ("command: '");
			TRACE_INFO ((char*)argv[i]);
			TRACE_INFO ("' Not found.\n\r");
		}
		i++;
	}
	return 0;
}

char ** complet (int argc, const char * const * argv)
{
	int j = 0;

	compl_world [0] = NULL;

	// if there is token in cmdline
	if (argc == 1)
	{
		// get last entered token
		char * bit = (char*) argv [argc-1];
		// iterate through our available token and match it
		for (int i = 0; i < _NUM_OF_CMD; i++)
		{
			// if token is matched (text is part of our token starting from 0 char)
			if (strstr(keyworld [i], bit) == keyworld [i])
			{
				// add it to completion set
				compl_world [j++] = keyworld [i];
			}
		}
	}
	else if ((argc > 1) && ((strcmp (argv[0], _CMD_SET)==0))) //||
							//(strcmp (argv[0], _CMD_CLR)==0)))
	{ // if command needs subcommands
		// iterate through subcommand
		for (int i = 0; i < _NUM_OF_SETCLEAR_SCMD; i++)
		{
			if (strstr (set_clear_key [i], argv [argc-1]) == set_clear_key [i])
			{
				compl_world [j++] = set_clear_key [i];
			}
		}
	}
	else
	{ // if there is no token in cmdline, just print all available token
		for (; j < _NUM_OF_CMD; j++)
		{
			compl_world[j] = keyworld [j];
		}
	}

	// note! last ptr in array always must be NULL!!!
	compl_world [j] = NULL;
	// return set of variants
	return compl_world;
}

void sigint (void)
{
	TRACE_INFO("\r\nSigint\r\n");
}

void putc_for_mrl(const char *fmt)
{
	int i = 0;
	while (fmt [i] != 0)
	{
		putchar(fmt[i]);
		i++;
	}
}

char mrl_get_char(void)
{
	char ch;

	_read (0, &ch, 1);

	return ch;
}

void help(void)
{
	TRACE_INFO("\n\rBC32X verison 1.0.\n\r");
	TRACE_INFO("\thelp   - this is HELP\n\r");
	TRACE_INFO("\tclear  - clear the terminal\n\r");
	TRACE_INFO("\tmonitor  - show tasks state\n\r");
	TRACE_INFO("\tget  - get enet params\n\r");
	TRACE_INFO("\tset  - set enet params\n\r");
	TRACE_INFO("\tread_exflash [addr] [n] - read n (1...2048) bytes from external flash by addr(hex)\n\r");
}

uint8_t check_digit(const char* fmt)
{
	for(uint8_t i = 0; fmt[i] != '\0'; i++)
		if( !isdigit( fmt[i] ))
			return 0;

	return 1;
}

void vUDPTask( void *pvParametrs )
{
	error_t error;
	size_t length;

	//Create a connectionless socket
	apEnParam->serverUDPSocket = socketOpen(SOCKET_TYPE_DGRAM, SOCKET_IP_PROTO_UDP);
	//Failed to create socket?
	if(!apEnParam->serverUDPSocket) { TRACE_INFO("Error to open UDP socket!\n"); }
	//Define a 15s timeout for all blocking operations
	error = socketSetTimeout(apEnParam->serverUDPSocket, 2);
	//Any error to report?
	if(error) { TRACE_INFO("Error to set timeout for UDP socket!\n"); }
	//Bind the newly created socket to port 4554
	error = socketBind(apEnParam->serverUDPSocket, &IP_ADDR_ANY, APP_UDP_PORT);
	if(error) { TRACE_INFO("Error to bind UDP socket!\n"); }

	uint8_t *bufferUDP = osAllocMem(MAX_UDPBUF_SIZE);

	for( ;; )
	{
		error = socketReceiveFrom(apEnParam->serverUDPSocket, apEnParam->clientIpAddrUDP,
		                          &apEnParam->clientPortUDP, bufferUDP, MAX_UDPBUF_SIZE, &length, 0);

		if(error == NO_ERROR)
        {
			 float * tmpp = osAllocMem(sizeof(float) * INPUT_MODEL_VECTOR_SIZE);

			 TickType_t start_time = xTaskGetTickCount();
			 for(uint16_t i = 0; i < INPUT_MODEL_VECTOR_SIZE; i++)
				 tmpp[i] = fabs(1 - (((float) bufferUDP[i]) / 255));

        	 float * tmpp2 = model_predict(tmpp);

        	 float time = (xTaskGetTickCount() - start_time) * portTICK_RATE_MS; // замерили время выполнения модели

        	 memcpy(bufferUDP, tmpp2, sizeof(float) * OUTPUT_MODEL_VECTOR_SIZE);
        	 memcpy((bufferUDP + sizeof(float) * OUTPUT_MODEL_VECTOR_SIZE), &time, sizeof(float)); // Записываем время выполнения

	 	 	 socketSendTo(apEnParam->serverUDPSocket, apEnParam->clientIpAddrUDP,
                     	  apEnParam->clientPortUDP, bufferUDP, sizeof(float) * OUTPUT_MODEL_VECTOR_SIZE + sizeof(float), 0, 0);
	 	 	 ;
	 	     osFreeMem(tmpp);
	 	 	 osFreeMem(tmpp2);
        }

        vTaskDelay( 2 );
	}
}

uint8_t CheckCommand(const uint8_t *data, size_t length)
{
	if(length != (data[2] + sizeof(header_t)) )         // Длина принятой посылки не совпадает с ожидаемой
		return 0;

	if(CalcCRC(&data[0], length - 2) == ( ((uint16_t) (data[length - 1]) << 8) | (data[length - 2])))
		return data[1];

	//TRACE_INFO("Header CRC is incorrect, com: %#u", data[1]);
	return FALSE;  //если CRC не совпадает, то отбрасываем команду
}
