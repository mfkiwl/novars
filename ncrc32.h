#ifndef __CRC32_H
#define __CRC32_H

int TestASCII(  char* ucBuf_ );
int TestBinary( unsigned char* ucBuf_, int iSize_ );

unsigned long CalculateCRC(unsigned char* ucBuf_, int iSize_);

#endif

