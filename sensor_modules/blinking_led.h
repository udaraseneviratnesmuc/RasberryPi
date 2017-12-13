#define LedPin 8

void lightLed(){
	pinMode(LedPin, OUTPUT);

	while(1){
		digitalWrite(LedPin, HIGH);
		printf("LED On");
		delay(1000);
		digitalWrite(LedPin, LOW);
		printf("LED Off");
		delay(1000);
	}

}