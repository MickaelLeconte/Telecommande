/*
 * com_bluetooth.h
 *
 *  Created on: 3 oct. 2018
 *      Author: mleconte
 */

#ifndef BLEUTOOTH_COM_BLUETOOTH_H_
#define BLEUTOOTH_COM_BLUETOOTH_H_

#include <SoftwareSerial.h>
#include "../key.h"

#define MAX_TRAME_SIZE 16

class BluetoothManager{
private:


	void ack(bool ACK);
	void send_data();
	byte checksum_calculator();

	int length;
	byte csum;

public:
	SoftwareSerial btSerial;
	BluetoothManager();
	byte key;
	void init();
	bool checksum();

	void reponse_AU();
	void envoie_vitesse(int pwm_droite, int pwm_g);
	void envoie_eau(bool state);
	void envoie_vitesse_brosse(int vitesse_brosse);
	void envoie_AU(bool state);
};
typedef struct {
	int size;
	byte buffer[MAX_TRAME_SIZE];
} TRAME;


#endif /* BLEUTOOTH_COM_BLUETOOTH_H_ */
