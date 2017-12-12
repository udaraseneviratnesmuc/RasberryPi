#define BtnPin 8

void btnPressed(){
	pinMode(BtnPin, INPUT);

	while(1) {
        if(digitalRead(BtnPin) == LOW){
  			printf("Button Pressed \n");
        }
    }

}