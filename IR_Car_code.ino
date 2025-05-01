
#include<IRremote.h>

const int RemotePin=8;
IRrecv irrecv(RemotePin);
decode_results results;

int in1=3;
int in2=5;
int in3=6;
int in4=9;

int buzzer = 13;
int frontLight = 12;
int backLight = 11;

int echopin = 2;
int trigpin = 3;
long duration;
float distance;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(frontLight, OUTPUT);
  pinMode(backLight, OUTPUT);
  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT);
}

void loop() {
    distance = Distance();
    if(TooClose(distance)){
      Stop();
    }
    if(irrecv.decode(&results))
      {
        Serial.println(results.value, HEX);
        Serial.println(distance);
        if (results.value==0xFF629D)//Press UP Button
        { 
          Serial.println("hiii");
          Forward();
        }
        else if (results.value==0xFFA857)//Press Down Button
        { 
          Backward();
        }
         else if (results.value==0xFF22DD)//Press Left Button
        { 
          Left();
        }
        else if (results.value==0xFFC23D)//Press Right Button
        { 
          Right();
        }
        else if (results.value==0xFF02FD)//Stop
        { 
          Stop();
        }
        else if (results.value==0xFFE21D)//BUZZER
        {
          Buzzer();
        }
        else if (results.value==0xFFE01F)//BackLight
        {
          BackLight();
        }
        else if (results.value==0xFF906F)//FrontLight
        {
          FrontLight();
        }
        irrecv.resume();
    }
}
   
 
void Backward()
  {
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  }
 void Forward()
  {
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  }
 void Stop()
  {
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  }
  int Left()
    {
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    }
  int Right()
    {
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    }
  int Buzzer()
    {
    digitalWrite(buzzer, !digitalRead(buzzer));
    }
  int FrontLight()
    {
    digitalWrite(frontLight,!digitalRead(frontLight));
    }
  int BackLight()
    {
    digitalWrite(backLight,!digitalRead(backLight));
    }
  float Distance()
    {
      digitalWrite(trigpin,LOW);
      delayMicroseconds (2);
  
      digitalWrite (trigpin, HIGH) ;
      delayMicroseconds(10) ;
      digitalWrite(trigpin, LOW) ;

      duration = pulseIn (echopin, HIGH);
      return duration * 0.034 / 2.0;
    }
  bool TooClose(float dist){
    return dist <= 8;
  }
