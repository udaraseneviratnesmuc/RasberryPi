#define LdrPin 7

void isLightAvailable(){
	pinMode(LdrPin, INPUT);
	pullUpDnControl(LdrPin, PUD_DOWN);

    while(1){
		delay(1000);

		if(digitalRead(LdrPin) == HIGH){
  			printf("Light Available \n");
        }else{
        	printf("Light Not Available \n");
        }

    }
}