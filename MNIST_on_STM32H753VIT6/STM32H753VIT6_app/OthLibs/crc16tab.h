#ifndef _CRC16TAB_H_
#define _CRC16TAB_H_

unsigned short CompileCRC (unsigned short DCrc, unsigned char Data);
unsigned short CalcCRC(const unsigned char *buf, unsigned short count);
unsigned char CheckCRC(unsigned char* buf, unsigned short count);
//unsigned short MoveCalcCRC(unsigned char*, unsigned char*, unsigned short);
//void PlaceCRC(unsigned char* buf, unsigned short count);
#endif
