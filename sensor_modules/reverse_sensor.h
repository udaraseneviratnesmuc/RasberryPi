#define TRIG 7
#define ECHO 0
#define BUZZ 8

void reverse();
void reverseArrange();
int reverseGetCm();
void ringBuzzer();
void reverseAlert(int distance);

void reverse(){
	reverseArrange();
    while(1){
        delay(500);
        int distance = getCm();
        reverseAlert(distance);
        printf("Distance %dcm\n", getCm());
    }
}

void reverseArrange(){
	pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(BUZZ, OUTPUT);  

    digitalWrite(TRIG, LOW);
    delay(30);
}

int reverseGetCm(){
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(20);
    digitalWrite(TRIG, LOW);

    while(digitalRead(ECHO) == LOW);

    long startTime = micros();
    while(digitalRead(ECHO) == HIGH);
    long travelTime = micros() - startTime;

    int distance = travelTime/58;

    return distance;
}

void ringBuzzer(){
    delay(10);
    digitalWrite(BUZZ, HIGH);
    delay(200);
    digitalWrite(BUZZ, LOW);
}

void reverseAlert(int distance){
    if(distance < 100){
        ringBuzzer();
    }else{
        digitalWrite(BUZZ, LOW);
    }
}
