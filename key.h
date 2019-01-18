/*
 * KEY.h
 *
 *  Created on: 22 oct. 2018
 *      Author: mleconte
 */

#ifndef KEY_H_
#define KEY_H_
#include <Arduino.h>

enum KEY {
	ID_ROBOT=(byte)0xA0,
	ACK=(byte)0x50,

	AU=(byte)0x60,
	BROSSES=(byte)0x61,
	EAU=(byte)0x62,
	DEPLACEMENT=(byte)0x63,
	LAME=(byte)0x64,

	SUCCESS=(byte)0x10,
	ERROR_ACK=(byte)0x20,
	ERROR_CHECKSUM=(byte)0x22
};



#endif /* KEY_H_ */
