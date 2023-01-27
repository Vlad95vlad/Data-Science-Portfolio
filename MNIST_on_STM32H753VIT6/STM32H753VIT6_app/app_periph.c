/*
 * Periph.c
 *
 *  Created on: 12 апр. 2022 г.
 *      Author: tkachev
 */
#include "app_periph.h"
#include "app_interface.h"
#include "crc16tab.h"
#include "MX25L128.h"


#include "stm32h753xx.h"
#include "stm32h7xx_it.h"

#include "task.h"

app_periph_t app_periph;
app_os_resources_t app_os_res;

uint64_t Tim2SetGetTicks(uint8_t t)
{
	static uint64_t Tim2Ticks = 0;

	if(t) Tim2Ticks++;
	return Tim2Ticks;
}


void TIM2_IRQHandler(void)
{
  Tim2SetGetTicks(1);

  HAL_TIM_IRQHandler(app_periph.htim2);
}

void Board_Init(void)
{
	app_periph.huart1 = (UART_HandleTypeDef *) osAllocMem( sizeof(UART_HandleTypeDef) );
	app_periph.huart6 = (UART_HandleTypeDef *) osAllocMem( sizeof(UART_HandleTypeDef) );
	app_periph.huart7 = (UART_HandleTypeDef *) osAllocMem( sizeof(UART_HandleTypeDef) );
	app_periph.htim2 = (TIM_HandleTypeDef *) osAllocMem( sizeof(TIM_HandleTypeDef) );
	app_periph.hspi3 = (SPI_HandleTypeDef *) osAllocMem( sizeof(SPI_HandleTypeDef) );

	app_os_res.uart1_mutex = xSemaphoreCreateMutex();           		// ћьютекс дл защиты UART
	app_os_res.xQueueRX_TCP_MRL = xQueueCreate( 50 , sizeof(char) );    // очередь дл€ TCP - MRL приемна€

	MX_GPIO_Init();

	app_periph.huart1->Instance = USART1;
	/*app_periph.huart6->Init.BaudRate =*/ app_periph.huart1->Init.BaudRate = 115200;
	app_periph.huart1->Init.WordLength = UART_WORDLENGTH_8B;
	app_periph.huart1->Init.StopBits = UART_STOPBITS_1;
	app_periph.huart1->Init.Parity = UART_PARITY_NONE;
	app_periph.huart6->Init.Mode = app_periph.huart1->Init.Mode = UART_MODE_TX_RX;
	app_periph.huart6->Init.HwFlowCtl = app_periph.huart1->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	app_periph.huart6->Init.OverSampling = app_periph.huart1->Init.OverSampling = UART_OVERSAMPLING_16;
	app_periph.huart6->Init.OneBitSampling = app_periph.huart1->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	app_periph.huart6->Init.ClockPrescaler = app_periph.huart1->Init.ClockPrescaler = UART_PRESCALER_DIV1;
	app_periph.huart6->AdvancedInit.AdvFeatureInit = app_periph.huart1->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	MX_USART_UART_Init(app_periph.huart1);
	TRACE_INFO("USART1 is successfully inited.\r\n");
	app_periph.huart6->Instance = USART6;
	app_periph.huart6->Init.BaudRate = 115200;
	app_periph.huart6->Init.Parity = UART_PARITY_EVEN;
	app_periph.huart6->Init.WordLength = UART_WORDLENGTH_9B;
	app_periph.huart6->Init.StopBits = UART_STOPBITS_2;
	MX_USART_UART_Init(app_periph.huart6);
	TRACE_INFO("UART6 is successfully inited.\r\n");
	app_periph.huart7->Instance = UART7;
	app_periph.huart7->Init.BaudRate = 57600;
	app_periph.huart7->Init.WordLength = UART_WORDLENGTH_9B;
	app_periph.huart7->Init.StopBits = UART_STOPBITS_2;
	app_periph.huart7->Init.Parity = UART_PARITY_EVEN;
	app_periph.huart7->Init.Mode = UART_MODE_TX_RX;
	app_periph.huart7->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	app_periph.huart7->Init.OverSampling = UART_OVERSAMPLING_16;
	app_periph.huart7->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	app_periph.huart7->Init.ClockPrescaler = UART_PRESCALER_DIV1;
	app_periph.huart7->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	MX_USART_UART_Init(app_periph.huart7);
	TRACE_INFO("UART7 is successfully inited.\r\n");
	app_periph.hspi3->Instance = SPI3;
	app_periph.hspi3->Init.Mode = SPI_MODE_MASTER;
	app_periph.hspi3->Init.Direction = SPI_DIRECTION_2LINES;
	app_periph.hspi3->Init.DataSize = SPI_DATASIZE_8BIT;
	app_periph.hspi3->Init.CLKPolarity = SPI_POLARITY_LOW;
	app_periph.hspi3->Init.CLKPhase = SPI_PHASE_1EDGE;
	app_periph.hspi3->Init.NSS = SPI_NSS_SOFT;
	app_periph.hspi3->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	app_periph.hspi3->Init.FirstBit = SPI_FIRSTBIT_MSB;
	app_periph.hspi3->Init.TIMode = SPI_TIMODE_DISABLE;
	app_periph.hspi3->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	app_periph.hspi3->Init.CRCPolynomial = 0x0;
	app_periph.hspi3->Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	app_periph.hspi3->Init.NSSPolarity = SPI_NSS_POLARITY_HIGH;
	app_periph.hspi3->Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
	app_periph.hspi3->Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	app_periph.hspi3->Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	app_periph.hspi3->Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
	app_periph.hspi3->Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
	app_periph.hspi3->Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
	app_periph.hspi3->Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
	app_periph.hspi3->Init.IOSwap = SPI_IO_SWAP_DISABLE;
    if (HAL_SPI_Init(app_periph.hspi3) != HAL_OK)
    {
    	Error_Handler();
    }
    TRACE_INFO("SPI3 is successfully inited.\r\n");
    //FindFlash( );
}


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET); // SPI CS (PA15)

  /*Configure GPIO pin : PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  CS_OFF;
}

void MX_USART_UART_Init(UART_HandleTypeDef * huart)
{
  if(huart->Instance==UART7)
  {
	  if(HAL_HalfDuplex_Init(huart) != HAL_OK)
	  {
		  Error_Handler();
	  }

	  if (HAL_UARTEx_EnableFifoMode(huart) != HAL_OK)
	  {
		  Error_Handler();
	  }
  }
  else if(huart->Instance == USART1 || huart->Instance == USART6)
  {
	  if (HAL_UART_Init(huart) != HAL_OK)
	  {
		Error_Handler();
	  }

	  if (HAL_UARTEx_EnableFifoMode(huart) != HAL_OK)
	  {
	     Error_Handler();
	  }
  }
  if (HAL_UARTEx_SetTxFifoThreshold(huart, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(huart, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }

}

void vConfigureTimerForRunTimeStats( void )
{
	// This function configures a timer that is used as the time base when
	//collecting run time statistical information - basically the percentage
	//of CPU time that each task is utilising.  It is called automatically when
	//the scheduler is started (assuming configGENERATE_RUN_TIME_STATS is set
	//to 1).
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	app_periph.htim2->Instance = TIM2;
	app_periph.htim2->Init.Prescaler = 23;
	app_periph.htim2->Init.CounterMode = TIM_COUNTERMODE_UP;
	app_periph.htim2->Init.Period = 9;
	app_periph.htim2->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	app_periph.htim2->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(app_periph.htim2) != HAL_OK)
    {
    	//Error_Handler();
    	TRACE_INFO("Could not init TIM2(for RTOS statistics).\r\n");
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(app_periph.htim2, &sClockSourceConfig) != HAL_OK)
    {
    	//Error_Handler();
    	TRACE_INFO("Could not init TIM2(for RTOS statistics).\r\n");
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(app_periph.htim2, &sMasterConfig) != HAL_OK)
    {
    	//Error_Handler();
    	TRACE_INFO("Could not init TIM2(for RTOS statistics).\r\n");
    }
    if(HAL_TIM_Base_Start_IT(app_periph.htim2) == HAL_OK)
    	TRACE_INFO("TIM2(for RTOS statistics) is successfully inited.\r\n");
}

void vCPLD_UV4( void *pvParametrs)
{
	uint8_t cpld;

	cpld = SendtoCPLD(WRITE_CPLD(configuration), 0x08, app_periph.huart7);
	TRACE_INFO("Sended to CPLD UV4-B: %x. Read 4byte from CPLD: %x \r\n", configuration, cpld);
	cpld = SendtoCPLD(WRITE_CPLD(status), 0x0, app_periph.huart7);
	TRACE_INFO("Sended to CPLD UV4-B: %x. Read status: %x \r\n", status, cpld);
	cpld = SendtoCPLD(WRITE_CPLD(configuration), 0x09, app_periph.huart7);
	TRACE_INFO("Sended to CPLD UV4-B: %x. Read 4byte from CPLD: %x \r\n", configuration, cpld);
	cpld = SendtoCPLD(WRITE_CPLD(status), 0x0, app_periph.huart7);
	TRACE_INFO("Sended to CPLD UV4-B: %x. Read status: %x \r\n", status, cpld);


	for(;;)
	{
		//0
		TRACE_INFO("0\r\n");
		cpld = SendtoCPLD(WRITE_CPLD(addr_flash_low), 0x00, app_periph.huart7);
		TRACE_INFO("Write to CPLD low addr: %#x. Read 4byte from CPLD: %#x\r\n", 0x00, cpld);
		cpld = SendtoCPLD(WRITE_CPLD(addr_flash_high), 0x00, app_periph.huart7);
		TRACE_INFO("Write to CPLD high addr: %#x. Read 4byte from CPLD: %#x\r\n", 0x00, cpld);
		//1
		TRACE_INFO("1\r\n");
		for(uint8_t j = input_data_flash0; j <= input_data_flash3; j++)
		{
			cpld = SendtoCPLD(WRITE_CPLD(j), j, app_periph.huart7);
			TRACE_INFO("Read com: %#x. Read 4byte from CPLD: %#x\r\n", WRITE_CPLD(j), cpld);
			vTaskDelay(2);
		}
		cpld = SendtoCPLD(READ_CPLD(0x3f), 0xfe, app_periph.huart7);
		TRACE_INFO("Read com: %#x. Read 4byte from CPLD: %#x\r\n", READ_CPLD(0x3f), cpld);
		//2
		TRACE_INFO("2\r\n");
		cpld = SendtoCPLD(WRITE_CPLD(addr_flash_low), 0x00, app_periph.huart7);
		TRACE_INFO("Write to CPLD low addr: %#x. Read 4byte from CPLD: %#x\r\n", 0x00, cpld);
		cpld = SendtoCPLD(WRITE_CPLD(addr_flash_high), 0x40, app_periph.huart7);
		TRACE_INFO("Write to CPLD high addr: %#x. Read 4byte from CPLD: %#x\r\n", 0x40, cpld);
		cpld = SendtoCPLD(READ_CPLD(0x3f), 0xfe, app_periph.huart7);
		TRACE_INFO("Read com: %#x. Read 4byte from CPLD: %#x\r\n", READ_CPLD(0x3f), cpld);
		vTaskDelay(120);
		//3
		TRACE_INFO("3\r\n");
		cpld = SendtoCPLD(WRITE_CPLD(addr_flash_low), 0x00, app_periph.huart7);
		TRACE_INFO("Write to CPLD low addr: %#x. Read 4byte from CPLD: %#x\r\n", 0x00, cpld);
		cpld = SendtoCPLD(WRITE_CPLD(addr_flash_high), 0x00, app_periph.huart7);
		TRACE_INFO("Write to CPLD high addr: %#x. Read 4byte from CPLD: %#x\r\n", 0x00, cpld);
		cpld = SendtoCPLD(READ_CPLD(0x3f), 0xfe, app_periph.huart7);
		TRACE_INFO("Read com: %#x. Read 4byte from CPLD: %#x\r\n", READ_CPLD(0x3f), cpld);
		for(uint8_t j = output_data_flash0; j <= output_data_flash3; j++)
		{
			cpld = SendtoCPLD(READ_CPLD(j), j, app_periph.huart7);
			TRACE_INFO("Read com: %#x. Read 4byte from CPLD: %#x\r\n", READ_CPLD(j), cpld);
			vTaskDelay(2);
		}
		//4
		TRACE_INFO("4\r\n");
		cpld = SendtoCPLD(WRITE_CPLD(addr_flash_low), 0x00, app_periph.huart7);
		TRACE_INFO("Write to CPLD low addr: %#x. Read 4byte from CPLD: %#x\r\n", 0x00, cpld);
		cpld = SendtoCPLD(WRITE_CPLD(addr_flash_high), 0x20, app_periph.huart7);
		TRACE_INFO("Write to CPLD high addr: %#x. Read 4byte from CPLD: %#x\r\n", 0x20, cpld);
		cpld = SendtoCPLD(READ_CPLD(0x3f), 0xfe, app_periph.huart7);
		TRACE_INFO("Read com: %#x. Read 4byte from CPLD: %#x\r\n", READ_CPLD(0x3f), cpld);
		vTaskDelay(6);
		//5
		TRACE_INFO("5\r\n");
		cpld = SendtoCPLD(WRITE_CPLD(addr_flash_low), 0x00, app_periph.huart7);
		TRACE_INFO("Write to CPLD low addr: %#x. Read 4byte from CPLD: %#x\r\n", 0x00, cpld);
		cpld = SendtoCPLD(WRITE_CPLD(addr_flash_high), 0x00, app_periph.huart7);
		TRACE_INFO("Write to CPLD high addr: %#x. Read 4byte from CPLD: %#x\r\n", 0x00, cpld);
		cpld = SendtoCPLD(READ_CPLD(0x3f), 0xfe, app_periph.huart7);
		TRACE_INFO("Read com: %#x. Read 4byte from CPLD: %#x\r\n", READ_CPLD(0x3f), cpld);
		for(uint8_t j = output_data_flash0; j <= output_data_flash3; j++)
		{
			cpld = SendtoCPLD(READ_CPLD(j), j, app_periph.huart7);
			TRACE_INFO("Read com: %#x. Read 4byte from CPLD: %#x\r\n", READ_CPLD(j), cpld);
			vTaskDelay(2);
		}

		TRACE_INFO("The end of cpld4 cycle.\r\n");
		vTaskDelay(200);
	}
}

void vCPLD_UV9( void *pvParametrs)
{
	uint8_t cpld;

	cpld = SendtoCPLD(WRITE_CPLD(configuration), 0x00, app_periph.huart6);
	TRACE_INFO("Sended to CPLD UV9-B: %x. Read 4byte from CPLD: %x \r\n", configuration, cpld);
	cpld = SendtoCPLD(WRITE_CPLD(status_cpld_uv9), 0x0, app_periph.huart6);
	TRACE_INFO("Sended to CPLD UV9-B: %x. Read status: %x \r\n", status_cpld_uv9, cpld);
	cpld = SendtoCPLD(WRITE_CPLD(configuration), 0x01, app_periph.huart6);
	TRACE_INFO("Sended to CPLD UV9-B: %x. Read 4byte from CPLD: %x \r\n", configuration, cpld);
	cpld = SendtoCPLD(WRITE_CPLD(status_cpld_uv9), 0x0, app_periph.huart6);
	TRACE_INFO("Sended to CPLD UV9-B: %x. Read status: %x \r\n", status_cpld_uv9, cpld);




	for(;;)
	{
		TransmitUartPedal(pedal_uart_3, 0x1);
		cpld = RecieveUartPedal(pedal_uart_3);
		TRACE_INFO("Readed from UART3: %#x\r\n", cpld);

		vTaskDelay(200);
	}
}

uint8_t SendtoCPLD(uint8_t com, uint8_t data, UART_HandleTypeDef *huart)
{
	uint8_t len = 1;
	uint8_t cpld_prot[4] = {0xAA, com, data, 0};

	if(huart->Instance == UART7)
	{
		HAL_HalfDuplex_EnableTransmitter(huart);
		HAL_HalfDuplex_EnableReceiver(huart);
		len = 4;
	}
	HAL_UART_Transmit(huart, cpld_prot, sizeof(cpld_prot) - 1, 100);
	HAL_UART_Receive(huart, cpld_prot, len, 10);

	return huart->Instance == UART7 ? cpld_prot[3] : cpld_prot[0];
}

uint8_t RecieveUartPedal(uint8_t uart_num)
{
	uint8_t uart_conf = uart1_config;
	uint8_t uart_rx = uart1_rx_data;

	if(uart_num == pedal_uart_2)
	{
		uart_conf = uart2_config;
		uart_rx = uart2_rx_data;
	}
	else if(uart_num == pedal_uart_3)
	{
		uart_conf = uart3_config;
		uart_rx = uart3_rx_data;
	}

	uint8_t cpld = SendtoCPLD(READ_CPLD(uart_conf), 0x0, app_periph.huart6);
	uint8_t timer_count = 5; // 5 мс
	while( ((cpld & 0x10) != 0x10) && timer_count)
	{
		vTaskDelay(1);
		cpld = SendtoCPLD(READ_CPLD(uart_conf), 0x0, app_periph.huart6);
		timer_count--;
	}

	if((cpld & 0x10) == 0x10)
		return SendtoCPLD(READ_CPLD(uart_rx), 0x0, app_periph.huart6);
	else
	return 0;
}

void TransmitUartPedal(uint8_t uart_num, uint8_t data)
{
	uint8_t uart_conf = uart1_config;
	uint8_t uart_tx = uart1_tx_data;
	uint8_t cpld;

	if(uart_num == pedal_uart_2)
	{
		uart_conf = uart2_config;
		uart_tx = uart2_tx_data;
	}
	else if(uart_num == pedal_uart_3)
	{
		uart_conf = uart3_config;
		uart_tx = uart3_tx_data;
	}

	while((SendtoCPLD(READ_CPLD(uart_conf), 0x0, app_periph.huart6) & 0x01) == 1);
	cpld = SendtoCPLD(WRITE_CPLD(uart_tx), data, app_periph.huart6);
	cpld = SendtoCPLD(WRITE_CPLD(uart_conf), 80, app_periph.huart6);   // ѕишем 1 в бит TX_STATE
}

/*
void SavetoFlashCrc(uint32_t Addr, uint8_t *Data, uint32_t datalength, uint8_t erase)
{
	if(erase)
		SectorErase(Addr & 0xff0000);

	uint16_t crc = CalcCRC(Data, datalength);
	uint8_t tmp[2] = {*(Data + datalength), *(Data + datalength + 1)};

	*(Data + datalength) = (uint8_t) (crc >> 8);
	*(Data + datalength + 1) = (uint8_t) crc;

	PageProgramm(Addr, Data, datalength + 2);

	*(Data + datalength) = tmp[0];
	*(Data + datalength + 1) = tmp[1];
}
*/

void ReadEnet(Enet_Param_t *ptr)
{
	uint16_t size_p = sizeof(Enet_Param_t) + 2;
	uint8_t *temp = (uint8_t *) osAllocMem(size_p);

	//ReadM25_Buf(0x000F0000, temp, size_p);

	if(CalcCRC(temp, sizeof(Enet_Param_t)) == (((uint16_t) temp[size_p - 2] << 8) | temp[size_p - 1]))
	{
		uint_t n = sizeof(ptr->myPassword);
		memcpy(ptr->myPassword, temp, n);
		memcpy(ptr->myMAC, temp + n, sizeof(ptr->myMAC));
		n += sizeof(ptr->myMAC);
		memcpy(ptr->myIP, temp + n, sizeof(ptr->myIP));
		n += sizeof(ptr->myIP);
		memcpy(ptr->myMASK, temp + n, sizeof(ptr->myMASK));
		n += sizeof(ptr->myMASK);
		memcpy(ptr->myGTW, temp + n, sizeof(ptr->myGTW));
	    ptr->Http = ((uint16_t) temp[size_p - 3] << 8) | temp[size_p - 4];
	}
	else
	{
		TRACE_INFO("CRC for enet params that was read from flash is not correct.\r\n");
		TRACE_INFO("Default params were selected.\r\n");

		uint8_t *tmp;
		memcpy(ptr->myMAC, (const uint8_t* ) (tmp = APP_MAC_ADDR), sizeof(APP_MAC_ADDR));
		memcpy(ptr->myIP, (const uint8_t* ) (tmp = APP_IPV4_HOST_ADDR), sizeof(APP_IPV4_HOST_ADDR));
		memcpy(ptr->myMASK, (const uint8_t* ) (tmp = APP_IPV4_SUBNET_MASK), sizeof(APP_IPV4_SUBNET_MASK));
		memcpy(ptr->myGTW, (const uint8_t* ) (tmp = APP_IPV4_DEFAULT_GATEWAY), sizeof(APP_IPV4_DEFAULT_GATEWAY));
		memcpy(ptr->myPassword, (const uint8_t* ) (tmp = APP_PASSWORD), sizeof(APP_PASSWORD));
		ptr->Http = HTTPS_PORT;
	}

	char const * tkn_arr [1] = {"get"};
	execute (1, tkn_arr);
	osFreeMem(temp);
}
