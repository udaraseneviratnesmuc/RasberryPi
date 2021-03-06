#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "sensor_modules/blinking_led.h"
#include "sensor_modules/btn_input.h"
#include "sensor_modules/buzzer.h"
#include "sensor_modules/ultra_sound.h"
#include "sensor_modules/reverse_sensor.h"
#include "sensor_modules/humidity.h"
#include "sensor_modules/ldr.h"
#include "sensor_modules/night_led.h"
#include "broadcasting_module/udp_broadcast_svr.h"

int setupWiringPi();
void showSampleMenu();
void triggureAction(int *choice);

int main(void) {
        
	setupWiringPi();

	showSampleMenu();

    return 0;
}


void showSampleMenu(){
	int choice;

	printf("########### Choose a Sample Circuit below ############\n");
	printf("1 - Blinking LED [Anode PIN 8] \n");
	printf("2 - Get button input [Connection PIN 8] \n");
	printf("3 - Ring Buzzer [Anode PIN 8] \n");
	printf("4 - Ultra sound distance detector [VCC PIN 5V, Trig PIN 7, Echo PIN 0] \n");
	printf("5 - Reverse Sensor [VCC PIN 5V, Trig PIN 7, Echo PIN 0, Buzzor Anode 8] \n");
	printf("6 - Humidity Sensor [VCC PIN 5V, Trig PIN 7] \n");
	printf("7 - Start signal broadcasting \n");
	printf("8 - LDR [Anode Pin 7] \n");
	printf("9 - Night LED [LDR GPIO 7, LED GPIO 8] \n\n");

	printf("Enter the choice index :");
	scanf("%d", &choice);

	triggureAction(&choice);
}

void triggureAction(int *choice){
	int action = *choice;

	switch(action){
		case 1 :
			lightLed();
		break;
		case 2:
			btnPressed();
		break;
		case 3:
			buzz();
		break;
		case 4:
			getDistance();
		break;
		case 5:
			reverse();
		break;
		case 6:
			readHumidity();
		break;
		case 7:
			doBroadcast();
		break;
		case 8:
			isLightAvailable();
		break;
		case 9:
			turnOnNightLed();
		break;
	}
}

int setupWiringPi(){
	if(wiringPiSetup() == -1) { //when initialize wiringPi failed, print message to screen
            printf("setup wiringPi failed !\n");
            return -1;
    }
}