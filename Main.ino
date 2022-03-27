#include <Servo.h>

Servo servoMotor1;
Servo servoMotor2;

const int Buzzer = 2;
const int Push = 3;
const int Led = 4;
const int Trigger = 12;
const int Echo = 13;

long t; //timepo que demora en llegar el eco
long distanciactual; //distancia en centimetros
bool PushState;
int SystemState;    //0: rampa arriba-bajando  1: rampa abajo-subiendo
int angle;

void Ultrasonico();
void Alerta();

void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación

  pinMode(Buzzer, OUTPUT); //pin como salida
  pinMode(Push, INPUT); //pin como salida
  pinMode(Led, OUTPUT); //pin como salida
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  servoMotor1.attach(10);
  servoMotor2.attach(11);
  
  digitalWrite(Trigger, LOW);
  digitalWrite(Buzzer, LOW);
  servoMotor1.write(0);
  servoMotor2.write(90);
  SystemState=0;
  t=0;
  distanciactual=0;
}

void loop(){

  PushState = digitalRead(Push);

  if(SystemState==0 && PushState==true){            //////Rampa arriba-bajando
      SystemState=1;
      Ultrasonico();
      angle=0;
      while(angle<=90 /*&& distanciactual>4*/){
          servoMotor1.write(angle);
          servoMotor2.write(90-angle);
          Alerta();    
          angle+=5;
          Ultrasonico();
          Serial.println(angle);
          //delay(50);
      }
    }else if(SystemState==1 && PushState==true){    //////Rampa abajo-subiendo
      SystemState=0;
      angle=0;
      while(angle<=90 /*&& distanciactual>4*/){
          servoMotor1.write(90-angle);
          servoMotor2.write(angle);
          Alerta();    
          angle+=8;
          Ultrasonico();
          Serial.println(angle);
          //delay(50);
      }     
      /*while(angle-i>=0){
          servoMotor1.write(angle-i);
          servoMotor2.write(90-angle+i);
          Alerta();    
          i+=5;
      }*/
    }
}

void Ultrasonico(){


  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  distanciactual = t/59;             //escalamos el tiempo a una distancia en cm
  
  Serial.print("Distancia: ");
  Serial.print(distanciactual);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  delay(100);          //Hacemos una pausa de 100ms
  
  ////////////////
  //led();
  ////////////////
}

/*void buzzer(){
  digitalWrite(Buzzer, HIGH);
  delay(150);
  digitalWrite(Buzzer, LOW);
  delay(150);
  digitalWrite(Buzzer, HIGH);
  delay(150);
  digitalWrite(Buzzer, LOW);
  }*/

void Alerta(){
  digitalWrite(Led, HIGH);
  digitalWrite(Buzzer, HIGH);
  delay(150);
  digitalWrite(Led, LOW);
  digitalWrite(Buzzer, LOW);
  delay(150);
  }
