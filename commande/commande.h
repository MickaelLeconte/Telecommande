/*
 * commande.h
 *
 *  Created on: 19 déc. 2018
 *      Author: mleconte
 */

#ifndef COMMANDE_COMMANDE_H_
#define COMMANDE_COMMANDE_H_


#include "../key.h"

#define Pin_potar_brosses A6
#define Pin_vitesse_rapide 12
#define Pin_eau 4
#define Pin_brosses 7
#define PIN_JOY_X A4 // X Axis Output
#define PIN_JOY_Y A3 // Y Axis Output
#define PIN_RESET A2 // Center Detect

#define resolution_analogue 1024
#define plage_potar 0.8 //0.5 -> 4.5V

class TelecommandeManager{

private:
	int val_joy_y_init;
	int val_joy_x_init;
	int val_joy_y;
	int val_joy_x;
	int traction;
	int direction;
	int rapport;

public:
	TelecommandeManager();

	int pwm_d;
	int pwm_g;
	int resolution_PWM;
	void init();
	int vitesse_brosses();
	void deplacement();
};

#endif /* COMMANDE_COMMANDE_H_ */
