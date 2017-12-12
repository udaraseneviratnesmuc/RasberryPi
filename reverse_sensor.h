#define TRIG 7
#define ECHO 0
#define BUZZ 2

void reverse();
static void arrange();
static int getCm();
void ringBuzzer();

void reverse(){
	arrange();
    while(1){
        delay(500);
        printf("Distance %dcm\n", getCm());
    }
}

void arrange(){
	pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(BUZZ, OUTPUT);  

    digitalWrite(TRIG, LOW);
    delay(30);
}

int getCm(){
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(20);
    digitalWrite(TRIG, LOW);

    while(digitalRead(ECHO) == LOW);

    long startTime = micros();
    while(digitalRead(ECHO) == HIGH);
    long travelTime = micros() - startTime;

    int distance = travelTime/58;

    if(distance > 15){
            ringBuzzer();
    }else{
            digitalWrite(BUZZ, LOW);
    }

    return distance;
}

void ringBuzzer(){
    delay(2000);
    digitalWrite(BUZZ, HIGH);
    delay(500);
    digitalWrite(BUZZ, LOW);
}
