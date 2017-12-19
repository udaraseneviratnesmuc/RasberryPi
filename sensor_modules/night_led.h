#define LdrPin 7
#define LedPin 8

void turnOnNightLed(){
	pinMode(LdrPin, INPUT);
    pinMode(LedPin, OUTPUT);
	pullUpDnControl(LdrPin, PUD_DOWN);

    while(1){
		delay(1000);

		if(digitalRead(LdrPin) == HIGH){
  			digitalWrite(LedPin, LOW);
            printf("Light Available \n");
        }else{
            digitalWrite(LedPin, HIGH);
        	printf("Light Not Available \n");
        }

    }
}