/*
 * MX25L128.c
 *
 *  Created on: 29 рту. 2022 у.
 *      Author: tkachev
 */

#include "MX25L128.h"
#include "app_periph.h"

extern app_periph_t app_periph;

#ifdef M25P80
void FindFlash(void)
{
	uint32_t flash_id = ReadIdentification();
	if(flash_id == 0x20201410)
		TRACE_INFO("Flash M25P80\r\n");

	//if( (flash_id & 0xffffff00) == 0xC2201800)
	//	TRACE_INFO("Flash MX25L128\r\n");

	else
		TRACE_INFO("Flash identification is not valid!\r\n");

	TRACE_INFO("Flash manufacturer identification: %#x\r\n", ((uint8_t) (flash_id >> 24)));
	TRACE_INFO("Memory type: %#x\r\n", ((uint8_t) (flash_id >> 16)));
	TRACE_INFO("Memory capacity: %#x\r\n", ((uint8_t) (flash_id >> 8)));
	/*TRACE_INFO("CFD length: %#x\r\n\n", (uint8_t) flash_id);*/
}

uint32_t ReadIdentification(void)
{
	uint8_t com = RDID;
	uint8_t device_id[4];
	CS_ON;
	HAL_SPI_Transmit(app_periph.hspi3, &com, 1, 0);
	HAL_SPI_Receive(app_periph.hspi3, device_id, sizeof(device_id), 100);
	CS_OFF;

	return ((uint32_t) device_id[0] << 24) | ((uint32_t) device_id[1] << 16) | ((uint32_t) device_id[2] << 8) | (device_id[3]);
}

uint8_t ReadStatusRegister(void)
{ 								                     // The READ STATUS REGISTER command allows the status register to be read.
	uint8_t rv = RDSR;                               // The status register may be read at any time, even while a PROGRAM, ERASE, or WRITE STATUS
	CS_ON;                                           // REGISTER cycle is in progress. When one of these cycles is in progress, it is recommended
	HAL_SPI_Transmit(app_periph.hspi3, &rv, 1, 10);  // to check the write in progress (WIP) bit before sending a new command to the device.
	HAL_SPI_Receive(app_periph.hspi3, &rv, 1, 50);   // It is also possible to read the status register continuously.
	CS_OFF;
	return rv;
}

void WriteEnable(void)
{
	uint8_t rv = WREN;					 		           // The WRITE ENABLE command sets the write enable latch (WEL) bit.
	CS_ON;                                                 // The WEL bit must be set before execution of every PROGRAM, ERASE, and WRITE command.
	HAL_SPI_Transmit(app_periph.hspi3, &rv, 1, 10);        // The WRITE ENABLE command is entered by driving chip select(CS) LOW, sending the
	CS_OFF;                                                // command code, and then driving CS HIGH.
}


void BulkErase(void)
{
	while(ReadStatusRegister() & 0x01);    // Waiting while bit0(write in progress) of Flash RDSR is 1.
	WriteEnable();                         // Before BulkErase can be accepted, a Write Enable (WREN) instruction must previously have been executed.
	CS_ON;
	uint8_t rv = BE;
	HAL_SPI_Transmit(app_periph.hspi3, &rv, 1, 10);
	CS_OFF;
}

void SendAddrtoFlash(uint32_t Addr)
{
	uint8_t *ptr = (uint8_t *) &Addr;
	HAL_SPI_Transmit(app_periph.hspi3, ptr, 3, 10);
}

void SectorErase(uint32_t Addr)
{
	while(ReadStatusRegister() & 0x01);   // Waiting while bit0(write in progress) of Flash RDSR is 1.
	WriteEnable();                        //  Before SectorErase can be accepted, a Write Enable (WREN) instruction must previously have been executed.

	CS_ON;
	uint8_t com = SE;
	HAL_SPI_Transmit(app_periph.hspi3, &com, 1, 10);

	SendAddrtoFlash(Addr);
	CS_OFF;
}

void SectorEraseNum(uint32_t Addr)
{
	while(ReadStatusRegister() & 0x01);   // Waiting while bit0(write in progress) of Flash RDSR is 1.
	WriteEnable();                        //  Before SectorErase can be accepted, a Write Enable (WREN) instruction must previously have been executed.

	CS_ON;
	uint8_t com = SE;
	HAL_SPI_Transmit(app_periph.hspi3, &com, 1, 10);

	SendAddrtoFlash(Addr << 16);
	CS_OFF;
}

void PageProgramm(uint32_t Addr, uint8_t *Data, uint32_t datalength)
{ 											         // The PAGE PROGRAM command allows bytes in the memory to be programmed, which means the bits are changed from 1 to 0.
	while(ReadStatusRegister() & 0x01); 	         // Waiting while bit0(write in progress) of Flash RDSR is 1.
	WriteEnable();                     		         // Before a PAGE PROGRAM command can be accepted a WRITE ENABLE command must be executed.

	CS_ON;                                           // The PAGE PROGRAM command is entered by driving chip select (S#) LOW
	uint8_t com = PP;                                // followed by the instruction code,
	HAL_SPI_Transmit(app_periph.hspi3, &com, 1, 10);

	SendAddrtoFlash(Addr);

	HAL_SPI_Transmit(app_periph.hspi3, Data, datalength, 10);
	CS_OFF;
}

uint8_t ReadM25_8bit(uint32_t Addr)
{
	uint8_t rv = READ;
	while(ReadStatusRegister() & 0x01);              // Waiting while bit0(write in progress) of Flash RDSR is 1.
	CS_ON;

	HAL_SPI_Transmit(app_periph.hspi3, &rv, 1, 10);

	SendAddrtoFlash(Addr);

	HAL_SPI_Receive(app_periph.hspi3, &rv, 1, 50);
	CS_OFF;

    return rv;
}

void ReadM25_Buf(uint32_t Addr, uint8_t *RxBuf, uint32_t bufsize)
{
	uint8_t com = READ;
	while(ReadStatusRegister() & 0x01);              // Waiting while bit0(write in progress) of Flash RDSR is 1.
	CS_ON;

	HAL_SPI_Transmit(app_periph.hspi3, &com, 1, 10);

	SendAddrtoFlash(Addr);

	HAL_SPI_Receive(app_periph.hspi3, RxBuf, bufsize, 50);
	CS_OFF;
}
#endif

/**
 * @Brief SPI Sends data for the specified length
   * @Param BUF - Send data buffer first address
   * @Param size - number of bytes to send data
   * @retval successfully returns Hal_ok
 */
static HAL_StatusTypeDef SPI_Transmit(uint8_t* send_buf, uint16_t size)
{
	return HAL_SPI_Transmit(app_periph.hspi3, send_buf, size, 100);
}

/**
   * @Brief SPI receives data for the specified length
   * @Param BUF - Receive data buffer first address
   * @Param size - Number of bytes to receive data
   * @retval successfully returns Hal_ok
 */
static HAL_StatusTypeDef SPI_Receive(uint8_t* recv_buf, uint16_t size)
{
	return HAL_SPI_Receive(app_periph.hspi3, recv_buf, size, 100);
}

/**
   * @Brief SPI receives data for the specified length while sending data
   * @Param Send_buf - Receive Data Buffer First Address
   * @Param Recv_buf - Receive data buffer first address
   * @Param Size - Number of bytes to send / receive data
   * @retval successfully returns Hal_ok
 */
static HAL_StatusTypeDef SPI_TransmitReceive(uint8_t* send_buf, uint8_t* recv_buf, uint16_t size)
{
	return HAL_SPI_TransmitReceive(app_periph.hspi3, send_buf, recv_buf, size, 100);
}

static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;

/**
     * @brief Waiting for timeout callback functions
  * @param  None.
  * @retval None.
  */
static  uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
    //  Wait a timeout process, output error message
	TRACE_INFO("SPI waiting timeout! ErrorCode = %D", errorCode);
	return 0;
}

/**
     * @brief uses the SPI to send a byte data
     * @Param Byte: Data to send
     * @RetVal Returns the received data
  */
uint8_t SPI_FLASH_SendByte(uint8_t byte)
{
	SPITimeout = SPIT_FLAG_TIMEOUT;

	// Wait for the send buffer as empty, TXE event
	while (__HAL_SPI_GET_FLAG( app_periph.hspi3, SPI_FLAG_TXE ) == RESET)
		if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(0);

	// Write the data register to write the data to be written to send buffers
	WRITE_REG(app_periph.hspi3->Instance->TXDR, byte);

	SPITimeout = SPIT_FLAG_TIMEOUT;

	// Wait for receiving buffer non-empty, RXNE event
	while (__HAL_SPI_GET_FLAG( app_periph.hspi3, SPI_FLAG_RXNE ) == RESET)
		if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);

	// Read the data register to get the received buffer data
	return READ_REG(app_periph.hspi3->Instance->RXDR);
}
#ifdef MX25L128
/**
   * @brief reads the ID inside the Flash
 * @param   none
   * @retval successfully returned device_id
 */
uint16_t M25LXX_ReadID(void)
{
    uint8_t recv_buf[2] = {0};    // RECV_BUF [0] Store Manufacture ID, Recv_buf [1] Store Device ID
    uint16_t device_id = 0;
    uint8_t send_data[4] = {REMS, 0, 0, 0}; // Wait to send data, command + address

    // Enable the selection
    CS_ON;

    // Send and read data
    if (HAL_OK == SPI_Transmit(send_data, 4))
    {
        if (HAL_OK == SPI_Receive(recv_buf, 2))
        {
            device_id = (recv_buf[0] << 8) | recv_buf[1];
        }
    }

    // Remove the film selection
    CS_OFF;

    return device_id;
}

/**
   * @brief reads M25LXX status registers, M25L128 has 2 status register and config register
   * @Param REG - Status Register Number (1 ~ 2)
   * @retval status register value
 */
uint8_t M25LXX_ReadSR(uint8_t reg)
{
    uint8_t result = 0;
    uint8_t send_buf[4] = {0x00, 0x00, 0x00, 0x00};

    switch(reg)
    {
        case 1:
            send_buf[0] = RDSR;
            break;
        case 2:
            send_buf[0] = RDCR;
            break;
        default:
            send_buf[0] = RDSR;
    }

    // Enable the selection * /
    CS_ON;

    if (HAL_OK == SPI_Transmit(send_buf, 4))
    {
        if (HAL_OK == SPI_Receive(&result, 1))
        {
            // Remove the film selection
			CS_OFF;

            return result;
        }
    }

    // Remove the film selection * /
    CS_OFF;

    return 0;
}

void M25LXX_Wait_Busy(void)
{
    while((M25LXX_ReadSR(1) & 0x01) == 0x01); // Waiting for the busy to clear
}

/**
   * @Brief M25LXX write enable, set the Wel set of S1 registers
 * @param    none
 * @retval
 */
void M25LXX_Write_Enable(void)
{
    uint8_t cmd = WREN;

    CS_ON;

    SPI_Transmit(&cmd, 1);

    CS_OFF;

    M25LXX_Wait_Busy();

}

/**
   * @brief M25LXX writes prohibition, clear Wel
 * @param    none
 * @retval    none
 */
void M25LXX_Write_Disable(void)
{
    uint8_t cmd = WRDI;

    CS_ON;

    SPI_Transmit(&cmd, 1);

    CS_OFF;

    M25LXX_Wait_Busy();
}

/**
   * @brief M25LXX erase a sector
   * @Param Sector_addr - sector address set according to actual capacity
 * @retval  none
   * @note blocking operation
 */
void M25LXX_Erase_Sector(uint32_t sector_addr)
{
	M25LXX_Write_Enable();  // Erase operation is written to 0xFF, you need to turn on write enable
    M25LXX_Wait_Busy();     // Waiting for write to complete

    // Enable the selection
    CS_ON;

    // Send sector erase instruction
    SPI_FLASH_SendByte(SE);
    // Send the high position of the sector address=
    SPI_FLASH_SendByte((sector_addr & 0xFF0000) >> 16);
    // Send the median of the sector address
    SPI_FLASH_SendByte((sector_addr & 0xFF00) >> 8);
    // Send the low position of the sector address
    SPI_FLASH_SendByte(sector_addr & 0xFF);

    // Remove the film selection
    CS_OFF;

    M25LXX_Wait_Busy();      // Waiting for sector erase completion
}

/**
   * @Brief page write operation
   * @Param Dat - The first address to be written
   * @Param Writeaddr - Address to write
   * @Param Byte_to_write - Number of bytes to be written (0-256)
 * @retval    none
 */
void M25LXX_PageProgram(uint8_t * dat, uint32_t WriteAddr, uint16_t nbytes)
{
    uint8_t cmd = PP;

    M25LXX_Write_Enable();

    // Enable the selection
    CS_ON;

    SPI_Transmit(&cmd, 1);

    uint8_t addr;
    HAL_StatusTypeDef status;
    // Send read address high
    addr = (WriteAddr & 0xFF0000) >> 16;
    status = SPI_Transmit(&addr, 1);
    // Send read address is mediated
    addr = (WriteAddr & 0xFF00) >> 8;
    status = SPI_Transmit(&addr, 1);
    // Send read address low
    addr = WriteAddr & 0xFF;
    status = SPI_Transmit(&addr, 1);

    SPI_Transmit(dat, nbytes);

    // Remove the film selection
    CS_OFF;

    M25LXX_Wait_Busy();
}

/**
   * @brief writes data for Flash, call this function, need to erase the sector before writing data
   * @Param PBuffer, pointer to write data
   * @Param WriteAddr, write address
   * @Param NumByToWrite, write data length
   * @retval no
 */
void M25LXX_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0;
    uint8_t NumOfSingle = 0;
    uint8_t Addr = 0;
    uint8_t count = 0;
    uint8_t temp = 0;

    // MOD operation is expensive, if Writeaddr is SPI_FLASH_PAGESIZE integration, the operation result is 0
    Addr = WriteAddr % SPI_FLASH_PageSize;
    // Bad count data value, just aligned to page address
    count = SPI_FLASH_PageSize - Addr;
    // Calculate how many integer pages to write
    NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
    // MOD operation is expensive, calculate the number of bytes of the remaining than one page
    NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

    // Addr = 0, then WriteAddr just press the page aligned
    if(Addr == 0)
    {
        // NumByteToWrite < SPI_FLASH_PageSize
        if(NumOfPage == 0)
        {
        	M25LXX_PageProgram(pBuffer, WriteAddr, NumByteToWrite);
        }
        // NumByteToWrite > SPI_FLASH_PageSize
        else
        {
            // Write the integer page first
            while(NumOfPage--)
            {
            	M25LXX_PageProgram(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr +=  SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }

            // If there are extra less than one page, write it
            M25LXX_PageProgram(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    // If the address is not aligned with SPI_FLASH_PAGESIZE
    else
    {
        // NumByteToWrite < SPI_FLASH_PageSize
        if(NumOfPage == 0)
        {
            // The remaining count of the current page is smaller than Numofsingle, can't write
            if(NumOfSingle > count)
            {
                temp = NumOfSingle - count;

                // First full of current page =
                M25LXX_PageProgram(pBuffer, WriteAddr, count);
                WriteAddr += count;
                pBuffer += count;

                // Remote the remaining data
                M25LXX_PageProgram(pBuffer, WriteAddr, temp);
            }
            // Current page remaining Count location can be written after Numofsingle data
            else
            {
            	M25LXX_PageProgram(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        // NumByteToWrite > SPI_FLASH_PageSize
        else
        {
            // Address does not separate the COUNT separately, do not join this operation
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
            NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

            M25LXX_PageProgram(pBuffer, WriteAddr, count);
            WriteAddr +=  count;
            pBuffer += count;

            // Write the integer page
            while(NumOfPage--)
            {
            	M25LXX_PageProgram(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr +=  SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }
            // If there are extra less than one page, write it * /
            if(NumOfSingle != 0)
            {
            	M25LXX_PageProgram(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/**
     * @brief reads Flash data
     * @Param PBuffer, store pointers that read data
     * @Param readaddr, read address
     * @Param Numbyteetoread, read data length
     * @retval no
  */
void M25LXX_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	M25LXX_Wait_Busy();

    // Select Flash: CS low
	CS_ON;

    // Send read instruction
    uint8_t cmd = READ;
    SPI_Transmit(&cmd, 1);

    uint8_t addr;
    HAL_StatusTypeDef status;
    // Send read address high
    addr = (ReadAddr & 0xFF0000) >> 16;
    status = SPI_Transmit(&addr, 1);
    // Send read address is mediated
    addr = (ReadAddr& 0xFF00) >> 8;
    status = SPI_Transmit(&addr, 1);
    // Send read address low
    addr = ReadAddr & 0xFF;
    status = SPI_Transmit(&addr, 1);

    if(HAL_OK == status)
        SPI_Receive(pBuffer, NumByteToRead);

    // Stop Signal Flash: CS High Level
    CS_OFF;
}
#endif
