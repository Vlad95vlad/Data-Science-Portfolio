/*
 * app_periph.h
 *
 *  Created on: 12 ���. 2022 �.
 *      Author: tkachev
 */

#ifndef APP_PERIPH_H_
#define APP_PERIPH_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32h7xx_hal.h"
#include "debug.h"
#include "app_enet.h"


#define READ_CPLD(X)   (X & 0x7F)
#define WRITE_CPLD(X)  (X | 0x80)


typedef struct
{
	TIM_HandleTypeDef *htim2;
	UART_HandleTypeDef *huart1;
	UART_HandleTypeDef *huart6;
	UART_HandleTypeDef *huart7;
	SPI_HandleTypeDef *hspi3;

} app_periph_t;

typedef struct
{
	xSemaphoreHandle uart1_mutex;
	xQueueHandle xQueueRX_TCP_MRL;
	uint8_t * fatfsbuf;

} app_os_resources_t;

typedef struct
{
	uint8_t TXSTART: 1;   // ����� �������� ������ (1)
	uint8_t R6: 1;
	uint8_t R5: 1;
	uint8_t R4: 1;
	uint8_t RXBUSY: 1;    // ��������� ��������� UART (1 - �����)
	uint8_t READY: 1;     // ���������� ����� ������ (1)
	uint8_t ERROR: 1;     // ������ ������ ����� ������ (1)
	uint8_t TXBUSY: 1;    // ��������� ����������� UART (1 - �����)

} pedal_uart_config_t;


/*typedef struct
{
	uint8_t uart0_cpld_conf;
	pedal_uart_config_t * uart1_pedal;
	pedal_uart_config_t * uart2_pedal;
	pedal_uart_config_t * uart3_pedal;

} cpld9_uarts_t;*/


enum cpld_uv4_commands
{
	po_version          = 0x00,   // ������ �� (R)
	configuration       = 0x01,   // ������������ (RW)
	test_rw             = 0x02,   // ���� RW (���������� �������� ����������� ��������) (RW)
	status              = 0x03,   // ������ (R)
	addr_flash_low      = 0x04,   // ������� ���� ������ ���� ������ (RW)
	addr_flash_high     = 0x05,   // ������� ���� ������ ���� ������ (RW)
	uart_freq_div       = 0x06,   // �������� ������� UART (������ 107) (RW)
	read_bloc_mem       = 0x07,   // ������ ������ ������� ������ (R)
	input_data_flash0   = 0x08,   // ������� ������ ����-������ (RW)
	input_data_flash1   = 0x09,   // ������� ������ ����-������ (RW)
	input_data_flash2   = 0x0A,   // ������� ������ ����-������ (RW)
	input_data_flash3   = 0x0B,   // ������� ������ ����-������ (RW)
	output_data_flash0  = 0x0C,   // �������� ������ ����-������ (RW)
	output_data_flash1  = 0x0D,   // �������� ������ ����-������ (RW)
	output_data_flash2  = 0x0E,   // �������� ������ ����-������ (RW)
	output_data_flash3  = 0x0F,   // �������� ������ ����-������ (RW)
    data_bloc_mem_start = 0x40,   // ������ ������� ������
	data_bloc_mem_end   = 0x7F
};

enum cpld_uv9_commands
{
	all_uart_freq_div     = 0x02,   // ������������ ������� UART0/1/2/3 (������ 27) (RW)
	uart0_divider         = 0x03,   // �������� ������� UART0 (������ 2) (RW)
	addr_flash_l          = 0x04,   // ������� ���� ������ ���� ������ (RW)
	addr_flash_mid        = 0x05,   // ������� ���� ������ ���� ������ (RW)
	addr_flash_h          = 0x06,   // ������� ���� ������ ���� ������ (RW)
	data_flash_start      = 0x08,   // ������ ����-������/psram/������� ������ (RW)
	data_flash_end        = 0x0F,   // ������ ����-������/psram/������� ������ (RW)
	port_upr_out_signs    = 0x10,   // ���� ���������� ��������� ��������� ��.32 (RW)
	port_upr_leds_stat    = 0x11,   // ���� ���������� ������������ ������ ��.32 (RW)
	port_upr_leds_pwr     = 0x12,   // ���� ���������� ������������ ������� ��.32 (RW)
	port_mask_psram       = 0x13,   // ���� ���������� ������ psram (������ - 0xFF) (RW)
	bs_in_line_state_0    = 0x14,   // ��������� ������� ����� ��.32 (R)
	bs_in_line_state_1    = 0x15,   // ��������� ������� ����� ��.32 (R)
	bs_in_line_state_2    = 0x16,   // ��������� ������� ����� ��.32 (R)
	status_cpld_uv9       = 0x17,   // ������ (R)
	configuration_adc     = 0x20,   // ������������ ��� MCP3202 (RW)
	freq_div_spi_adc      = 0x21,   // �������� ������� SPI ��� (������ - 25)(RW)
	freq_div_uart_1_2_3   = 0x22,   // �������� ������� UART[1...3] (������ - 2)(RW)
	uart_mode             = 0x23,   // ����� ������ UART (RW)
	uart1_tx_data         = 0x24,   // ������ ����������� UART1 (RW)
	uart1_rx_data         = 0x25,   // ������ ��������� UART1 (RW)
	uart1_config          = 0x26,   // ������������ UART1 (RW)
	uart2_tx_data         = 0x28,   // ������ ����������� UART2 (RW)
	uart2_rx_data         = 0x29,   // ������ ��������� UART2 (RW)
	uart2_config          = 0x2A,   // ������������ UART2 (RW)
	test_rw_cpld_uv9      = 0x2B,   // ���� RW (���������� �������� ����������� ��������) (RW)
	uart3_tx_data         = 0x2C,   // ������ ����������� UART3 (RW)
	uart3_rx_data         = 0x2D,   // ������ ��������� UART3 (RW)
	uart3_config          = 0x2E,   // ������������ UART3 (RW)
	memory_encod_state    = 0x2F,   // ��������� ����������� ������ ������ (R)
	adc_data_start_addr   = 0x30,   // 16-�� ��������� ������ �� 8 ������� ��� (R)
	adc_data_end_addr     = 0x3F,   // 16-�� ��������� ������ �� 8 ������� ��� (R)
    data_bloc_mem32_start = 0x40,   // ������ ������� ������ 32 ����� (RW)
	data_bloc_mem32_end   = 0x5F,   // ������ ������� ������ 32 ����� (RW)
};

enum pedal_uart
{
	pedal_uart_1 = 0x00,
	pedal_uart_2 = 0x01,
	pedal_uart_3 = 0x02
};

void Board_Init(void);
 	 void MX_GPIO_Init(void);
 	 void MX_USART_UART_Init(UART_HandleTypeDef * huart);

void vCPLD_UV4( void *pvParametrs);
void vCPLD_UV9( void *pvParametrs);
	 uint8_t SendtoCPLD(uint8_t com, uint8_t data, UART_HandleTypeDef *huart);
	 uint8_t RecieveUartPedal(uint8_t uart_num);
	 void TransmitUartPedal(uint8_t uart_num, uint8_t data);


uint8_t ReadStatusRegister(void);
void WriteEnable(void);
void BulkErase(void);
void SendAddrtoFlash(uint32_t Addr);
void SectorErase(uint32_t Addr);
void SectorEraseNum(uint32_t Addr);
void PageProgramm(uint32_t Addr, uint8_t *Data, uint32_t datalength);
uint8_t ReadM25_8bit(uint32_t Addr);
void ReadM25_Buf(uint32_t Addr, uint8_t *RxBuf, uint32_t bufsize);
void SavetoFlashCrc(uint32_t Addr, uint8_t *Data, uint32_t datalength, uint8_t erase);
void ReadEnet(Enet_Param_t *ptr);


#ifdef __cplusplus
}
#endif

#endif /* APP_PERIPH_H_ */
