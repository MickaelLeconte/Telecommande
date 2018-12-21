/*
 * com_bluetooth.cpp
 *
 *  Created on: 3 oct. 2018
 *      Author: mleconte
 */
#include "com_bluetooth.h"

TRAME trame;

BluetoothManager::BluetoothManager() : btSerial(6, 5){
	csum=0;
	length=0;
	key=-1;
}
void BluetoothManager::init(){
	btSerial.begin(115200);
	Serial.begin(115200);
}

byte BluetoothManager::checksum_calculator(){
	byte temp_size = trame.buffer[1];
	byte cksum = 0;
	for(int i=0;i<temp_size+1;i++){
		cksum=cksum+trame.buffer[i];
	}
	cksum=(~cksum)+1;
	return cksum;
}

void BluetoothManager::envoie_vitesse(int pwm_droit,int pwm_gauche){
	trame.buffer[0]=(ID_ROBOT); //start
	trame.buffer[1]=(0x06); //length
	trame.buffer[2]=(DEPLACEMENT); //code

	bool signe;

	if (pwm_droit>=0){signe=0;}
	else {
		signe=1;
		pwm_droit=abs(pwm_droit);
	}
	trame.buffer[3]=(byte)(((pwm_droit>>8) & 0x007F)+((signe<<7)&0x80));
	trame.buffer[4]=(byte)(pwm_droit & 0x00FF);

	if (pwm_gauche>=0){signe=0;}
	else {
		signe=1;
		pwm_gauche=abs(pwm_gauche);
	}
	trame.buffer[5]=(byte)(((pwm_gauche>>8) & 0x007F)+((signe<<7)&0x80));
	trame.buffer[6]=(byte)(pwm_gauche & 0x00FF);

	trame.buffer[7]=checksum_calculator();
	trame.size=(int)trame.buffer[1]+2;
	send_data();
}

void BluetoothManager::envoie_eau(bool state){
	trame.buffer[0]=(ID_ROBOT); //start
	trame.buffer[1]=(0x03); //length
	trame.buffer[2]=(EAU); //code
	trame.buffer[3]=(state); //code_resp
	trame.buffer[4]=checksum_calculator();
	trame.size=(int)trame.buffer[1]+2;
	send_data();
}

void BluetoothManager::envoie_vitesse_brosse(int vitesse_brosses){
	trame.buffer[0]=(ID_ROBOT); //start
	trame.buffer[1]=(0x03); //length
	trame.buffer[2]=(BROSSES); //code
	trame.buffer[3]=(vitesse_brosses); //code_resp
	trame.buffer[4]=checksum_calculator();
	trame.size=(int)trame.buffer[1]+2;
	send_data();
}

void BluetoothManager::envoie_AU(bool state){
	trame.buffer[0]=(ID_ROBOT); //start
	trame.buffer[1]=(0x03); //length
	trame.buffer[2]=(AU); //code
	trame.buffer[3]=(state); //code_resp
	trame.buffer[4]=checksum_calculator();
	trame.size=(int)trame.buffer[1]+2;
	send_data();
}

void BluetoothManager::send_data(){
	for(int i =0; i<trame.size; i++){
		btSerial.write(trame.buffer[i]);
		Serial.write(trame.buffer[i]);
	}
}
