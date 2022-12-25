/*
 * utels.h
 *
 * Created: 12/24/2022 3:24:33 PM
 *  Author: MANAL
 */ 


#ifndef UTELS_H_
#define UTELS_H_

#define SetBit(reg,bit)  reg |= (1<<bit)
#define ClearBit(reg,bit)  reg &= ~(1<<bit)
#define ToggleBit(reg,bit)  reg ^= (1<<bit)
#define ReadBit(reg,bit)  ((reg>>bit)&1)


#endif /* UTELS_H_ */