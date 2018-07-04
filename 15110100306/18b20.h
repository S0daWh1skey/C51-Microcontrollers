#ifndef __DS18B20_H__
#define __DS18B20_H__

#include<reg52.h>     
#include<intrins.h>

#define uchar unsigned char
#define uint   unsigned int;
sbit DQ=P2^5;
unsigned int ReadTemperature(void);
bit Reset_DS18B20(void);
unsigned char ReadOneChar(void);
void WriteOneChar(unsigned char dat);

#endif
