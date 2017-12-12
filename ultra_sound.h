#define TRIG 7
#define ECHO 0

void getDistance();
void arrange();
int getCm();

void getDistance(){
	arrange();
    while(1){
        delay(500);
        printf("Distance %dcm\n", getCm());
    }
}

void arrange(){
	pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

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

    return distance;
}