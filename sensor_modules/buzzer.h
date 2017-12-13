#define BuzzerPin 8

void buzz(){
	pinMode(BuzzerPin, OUTPUT);

    while(1){
            delay(2000);
            digitalWrite(BuzzerPin, HIGH);
            delay(500);
            digitalWrite(BuzzerPin, LOW);
    }
}