/*
 * app_periph.h
 *
 *  Created on: 12 апр. 2022 г.
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
	uint8_t TXSTART: 1;   // Старт передачи данных (1)
	uint8_t R6: 1;
	uint8_t R5: 1;
	uint8_t R4: 1;
	uint8_t RXBUSY: 1;    // Состояние приемника UART (1 - занят)
	uint8_t READY: 1;     // Готовность байта данных (1)
	uint8_t ERROR: 1;     // Ошибка приема байта данных (1)
	uint8_t TXBUSY: 1;    // Состояние передатчика UART (1 - занят)

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
	po_version          = 0x00,   // Версия ПО (R)
	configuration       = 0x01,   // Конфигурация (RW)
	test_rw             = 0x02,   // Тест RW (возвращает инверсию записанного значения) (RW)
	status              = 0x03,   // Статус (R)
	addr_flash_low      = 0x04,   // Младший байт адреса флэш памяти (RW)
	addr_flash_high     = 0x05,   // Старший байт адреса флэш памяти (RW)
	uart_freq_div       = 0x06,   // Делитель частоты UART (дефолт 107) (RW)
	read_bloc_mem       = 0x07,   // Чтение данных блочной памяти (R)
	input_data_flash0   = 0x08,   // Входные данные флэш-память (RW)
	input_data_flash1   = 0x09,   // Входные данные флэш-память (RW)
	input_data_flash2   = 0x0A,   // Входные данные флэш-память (RW)
	input_data_flash3   = 0x0B,   // Входные данные флэш-память (RW)
	output_data_flash0  = 0x0C,   // Выходные данные флэш-память (RW)
	output_data_flash1  = 0x0D,   // Выходные данные флэш-память (RW)
	output_data_flash2  = 0x0E,   // Выходные данные флэш-память (RW)
	output_data_flash3  = 0x0F,   // Выходные данные флэш-память (RW)
    data_bloc_mem_start = 0x40,   // Данные блочной памяти
	data_bloc_mem_end   = 0x7F
};

enum cpld_uv9_commands
{
	all_uart_freq_div     = 0x02,   // Предделитель частоты UART0/1/2/3 (дефолт 27) (RW)
	uart0_divider         = 0x03,   // Делитель частоты UART0 (дефолт 2) (RW)
	addr_flash_l          = 0x04,   // Младший байт адреса флэш памяти (RW)
	addr_flash_mid        = 0x05,   // Средний байт адреса флэш памяти (RW)
	addr_flash_h          = 0x06,   // Старший байт адреса флэш памяти (RW)
	data_flash_start      = 0x08,   // Данные флэш-памяти/psram/блочной памяти (RW)
	data_flash_end        = 0x0F,   // Данные флэш-памяти/psram/блочной памяти (RW)
	port_upr_out_signs    = 0x10,   // Порт управления выходными сигналами БС.32 (RW)
	port_upr_leds_stat    = 0x11,   // Порт управления светодиодами статус БС.32 (RW)
	port_upr_leds_pwr     = 0x12,   // Порт управления светодиодами питания БС.32 (RW)
	port_mask_psram       = 0x13,   // Порт управления маской psram (дефолт - 0xFF) (RW)
	bs_in_line_state_0    = 0x14,   // Состояние входных линий БС.32 (R)
	bs_in_line_state_1    = 0x15,   // Состояние входных линий БС.32 (R)
	bs_in_line_state_2    = 0x16,   // Состояние входных линий БС.32 (R)
	status_cpld_uv9       = 0x17,   // Статус (R)
	configuration_adc     = 0x20,   // Конфигурация АЦП MCP3202 (RW)
	freq_div_spi_adc      = 0x21,   // Делитель частоты SPI АЦП (дефолт - 25)(RW)
	freq_div_uart_1_2_3   = 0x22,   // Делитель частоты UART[1...3] (дефолт - 2)(RW)
	uart_mode             = 0x23,   // Режим работы UART (RW)
	uart1_tx_data         = 0x24,   // Данные передатчика UART1 (RW)
	uart1_rx_data         = 0x25,   // Данные приемника UART1 (RW)
	uart1_config          = 0x26,   // Конфигурация UART1 (RW)
	uart2_tx_data         = 0x28,   // Данные передатчика UART2 (RW)
	uart2_rx_data         = 0x29,   // Данные приемника UART2 (RW)
	uart2_config          = 0x2A,   // Конфигурация UART2 (RW)
	test_rw_cpld_uv9      = 0x2B,   // Тест RW (возвращает инверсию записанного значения) (RW)
	uart3_tx_data         = 0x2C,   // Данные передатчика UART3 (RW)
	uart3_rx_data         = 0x2D,   // Данные приемника UART3 (RW)
	uart3_config          = 0x2E,   // Конфигурация UART3 (RW)
	memory_encod_state    = 0x2F,   // Состояние дешифратора адреса памяти (R)
	adc_data_start_addr   = 0x30,   // 16-ти разрядные данные по 8 каналам АЦП (R)
	adc_data_end_addr     = 0x3F,   // 16-ти разрядные данные по 8 каналам АЦП (R)
    data_bloc_mem32_start = 0x40,   // Данные блочной памяти 32 байта (RW)
	data_bloc_mem32_end   = 0x5F,   // Данные блочной памяти 32 байта (RW)
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
