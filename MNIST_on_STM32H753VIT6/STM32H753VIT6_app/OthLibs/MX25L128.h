/*
 * MX25L128.h
 *
 *  Created on: 29 рту. 2022 у.
 *      Author: tkachev
 */

#ifndef MX25L128_H_
#define MX25L128_H_

#include "stm32h7xx_hal.h"


#define M25P80

#define RDID      0x9F  	   // Read Identification
#define PP        0x02         // Page Program
#define READ      0x03         // Read Data Bytes
#define FAST_READ 0x0B         // Read Data Bytes at Higher Speed
#define WREN      0x06  	   // Write Enable
#define WRDI      0x04 		   // Write Disable
#define RDSR      0x05  	   // Read Status Register
#define WRSR      0x01         // Write Status/Configuration(for MX25L128) Register
#define DP        0xB9         // Deep Power-down
#define RES       0xAB         // Release from Deep Power-down, and Read Electronic Signature | Release from Deep Power-down

#define CS_OFF      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
#define CS_ON       HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);

// Wait timeout
#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

uint8_t SPI_FLASH_SendByte(uint8_t byte);

#ifdef M25P80
/******************************M25P80(Extern NOR Flash) commands********************************************************************/
#define GET_FLASH_ADDR(SecNum, PageNum, ByteNum)  (ByteNum | (SecNum << 16) | (PageNum << 8))

#define SE 0xD8         // Sector Erase
#define BE 0xC7         // Bulk Erase

#define SECTOR15_START 	0x000F0000
#define END_FLASH_ADDR  0x000FEFFF

void FindFlash(void);
uint32_t ReadIdentification(void);
uint8_t ReadStatusRegister(void);
void WriteEnable(void);
void BulkErase(void);
void SendAddrtoFlash(uint32_t Addr);
void SectorErase(uint32_t Addr);
void SectorEraseNum(uint32_t Addr);
void PageProgramm(uint32_t Addr, uint8_t *Data, uint32_t datalength);
uint8_t ReadM25_8bit(uint32_t Addr);
void ReadM25_Buf(uint32_t Addr, uint8_t *RxBuf, uint32_t bufsize);
#endif


#ifdef MX25L128

#define ManufactDeviceID_CMD            0x90
#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256

#define READ2           0xBB
#define DREAD           0x3B
#define READ4           0xEB
#define QREAD           0x6B
#define PP4             0x38
#define SE              0x20         // Sector Erase
#define BE_32           0x52         // Block(32K) Erase
#define BE_64           0xD8         // Block(64K) Erase
#define CE              0x60         // Chip erase (60 or C7 hex)
#define RDCR            0x15         // Read configuration register
#define WPSEL           0x68         // To enter and endable individual block protect mode
#define EQIO            0x35         // Entering the QPI mode
#define RSTQIO          0xF5         // Exiting the QPI mode
#define PGM_ERS_SUSPEND 0xB0         // suspend programm/erase
#define PGM_ERS_RESUME  0x30         // resume programm/erase
#define SBL             0xC0         // Set burst length
#define RDFBR           0x16         // Read fast boot register
#define WRFBR           0x17         // Write fast boot register
#define ESFBR           0x18         // Erase fast boot register
#define REMS            0x90         // read electronic manufacturer & device ID

uint16_t M25LXX_ReadID(void);
uint8_t M25LXX_ReadSR(uint8_t reg);
void M25LXX_Wait_Busy(void);
void M25LXX_Write_Enable(void);
void M25LXX_Write_Disable(void);
void M25LXX_Erase_Sector(uint32_t sector_addr);
void M25LXX_PageProgram(uint8_t * dat, uint32_t WriteAddr, uint16_t nbytes);
void M25LXX_BufferWrite(uint8_t * pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void M25LXX_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
#endif

#endif /* MX25L128_H_ */
