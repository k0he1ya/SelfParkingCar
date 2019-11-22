#include <Servo.h>

Servo myservo;

int Echo =A4;
int Trig =A5;
int R_LED  =13;
int Y_LED=10;
int BackTrig=A2;
int BackEcho=A3;
int rightDistance=0;
int leftDistance=0;
int middleDistance=0;
int backDistance=0;
int flag=0;
unsigned long space=0;
unsigned long start_time=0;

#define ENB 5
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define ENA 6
#define carSpeed 80

void forward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(R_LED, LOW);
  Serial.println("Forward");
}

void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Back");
}

void left() {
  analogWrite(ENA, 435);
  analogWrite(ENB, 435);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Left");
}

void right() {
  analogWrite(ENA, 500);
  analogWrite(ENB, 500);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}

void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(R_LED, HIGH);
  Serial.println("Stop!");
}

int getDistance() {
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    return (int)pulseIn(Echo, HIGH) / 58;
}

int getBackDistance(){
  digitalWrite(BackTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(BackTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(BackTrig, LOW);
  return (int)pulseIn(BackEcho, HIGH) / 58;
}

void setup() {
  myservo.attach(3);

  Serial.begin(9600);

  pinMode(R_LED, OUTPUT);
  pinMode(Y_LED, OUTPUT);
  pinMode(BackEcho, INPUT);
  pinMode(BackTrig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();

}

void loop() {
  
  myservo.write(180); 
  delay(500);
  middleDistance = getDistance();
  backDistance=getBackDistance();

  while(flag==0 && middleDistance <= 20){
    forward();
    middleDistance=getDistance();
  }

  while(flag==0 && middleDistance >= 20){
    start_time=millis();
    flag=1;
    forward();
    middleDistance=getDistance();
  }

  while(flag==1 && middleDistance <= 20){
    unsigned long cur_time=millis();
    space=(cur_time - start_time);
    stop();
    delay(1000);
    digitalWrite(R_LED, LOW);
    delay(500);
    
    if(space<=1500){
      flag=2;
    }
    else{
      flag=5;
    }

    back();
    delay(500);
  }

  while(flag==2){
    right();
    delay(500);
    flag=3;
  }

  while(flag==3){
    back();
    delay(60);
    if(getBackDistance() <= 10){
      stop();
      //delay(1000);
      digitalWrite(R_LED, LOW);
      flag=4;
    }
  }

  while(flag==4){ //finish parking mode 
    stop();
    digitalWrite(R_LED, LOW);
    digitalWrite(Y_LED, HIGH);
    delay(1000);
    digitalWrite(Y_LED, LOW);
    delay(1000);
  }

  while(flag==5){
    right();
    delay(300);
    flag=6;
  }

  while(flag==6){
    back();
    if(getBackDistance()<=10){
      stop();
      delay(1000);
      digitalWrite(R_LED, LOW);
      flag=7;
    }
  }

  while(flag==7){
    left();
    flag=4;
  }

}
