/*
 * commande.cpp
 *
 *  Created on: 19 déc. 2018
 *      Author: mleconte
 */

#include "commande.h"


TelecommandeManager::TelecommandeManager(){
	val_joy_x_init=126;
	val_joy_y_init=126;
	val_joy_x=0;
	val_joy_y=0;
	traction=0;
	direction=0;
	rapport=0;
	resolution_PWM=255;
	pwm_d=0;
	pwm_g=0;
}

void TelecommandeManager::init(){

	pinMode(Pin_potar_brosses,INPUT);
	pinMode(Pin_brosses,INPUT_PULLUP);
	pinMode(Pin_eau,INPUT_PULLUP);
	pinMode(Pin_vitesse_rapide,INPUT_PULLUP);

	// Déclaration des pins d'acquisition du joystick
	pinMode(PIN_JOY_X,INPUT);
	pinMode(PIN_JOY_Y,INPUT);
	pinMode(PIN_RESET,INPUT_PULLUP);

	// Récupération du neutre
	val_joy_x_init=analogRead(PIN_JOY_X);
	val_joy_y_init=analogRead(PIN_JOY_Y);

}

int TelecommandeManager::vitesse_brosses(){
	int vitesse=analogRead(Pin_potar_brosses);
	return vitesse;
}

void TelecommandeManager::deplacement(){
	// Récupération des valeurs des axes
	val_joy_y = analogRead (PIN_JOY_Y);
	val_joy_x = analogRead (PIN_JOY_X);

	// Calcul de trajectoire
	traction = val_joy_x - val_joy_x_init;
	direction = val_joy_y - val_joy_y_init;

	// Calcul des pwm
	pwm_d = (traction + direction)/(resolution_analogue * plage_potar / resolution_PWM /2);
	pwm_g = (traction - direction)/(resolution_analogue * plage_potar / resolution_PWM /2);

	// Normalisation de la commande
	if(pwm_d>=resolution_PWM){pwm_d=resolution_PWM;}
	else if(pwm_d<=-resolution_PWM){pwm_d=-resolution_PWM;}

	if(pwm_g>=resolution_PWM){pwm_g=resolution_PWM;}
	else if(pwm_g<=-resolution_PWM){pwm_g=-resolution_PWM;}

}

