#include "Arduino.h"
#include "bleutooth/com_bluetooth.h"
#include "commande/commande.h"


BluetoothManager btManager;
TelecommandeManager telManager;

#define Pin_AU 2
bool AU_state=false;


void setup()

{

	pinMode(Pin_AU, INPUT_PULLUP);
	pinMode(LED_BUILTIN, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(Pin_AU), arret_urgence, FALLING);
	digitalWrite(LED_BUILTIN,0);

	btManager.init();
	telManager.init();
	digitalWrite(LED_BUILTIN,1);


}


void loop()
{
	digitalWrite(LED_BUILTIN,0);

	while(!AU_state){

		if(digitalRead(Pin_vitesse_rapide)){telManager.resolution_PWM=126;}
		else{telManager.resolution_PWM=255;}

		if(digitalRead(Pin_brosses)){btManager.envoie_vitesse_brosse(0);}
		else{btManager.envoie_vitesse_brosse(telManager.vitesse_brosses());}

		telManager.deplacement();
		btManager.envoie_vitesse(telManager.pwm_d,telManager.pwm_g);

		btManager.envoie_eau(!digitalRead(Pin_eau));
		delay(200);
	}

	btManager.envoie_AU(true);
	delay(1000);
	if(digitalRead(Pin_AU)){
		AU_state=false;
		btManager.envoie_AU(false);
		btManager.envoie_AU(false);
		btManager.envoie_AU(false);
	}


}

void arret_urgence() {
	AU_state=true;
}
