#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BT(10,11);
Servo servomotor;

char valor;
String estado;
int comunicacion = 7;
int led1 = 8;
int ledPWM = 6;
int gasPWM = 5;

int contGas = 0;
int contador = 0;

boolean bt = false;

boolean izq = false;
boolean der = false;



const int maxDeg = 130;
const int minDeg  = 45;
const int recDeg = -45;
int convertDeg  = minDeg - recDeg;

int currentDeg = (maxDeg - minDeg)/2;

void setup() {

  servomotor.attach(6); //Pin PWM 6 del Arduino para el servo
  //servomotor.write(0);  //Inicia el servo en una posición de 90 grados

  pinMode(7,OUTPUT);
  pinMode(8, OUTPUT);
  
  pinMode(comunicacion, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(ledPWM, OUTPUT);
  pinMode(gasPWM,OUTPUT);
  //digitalWrite(gasPWM, HIGH);
  analogWrite(gasPWM,0);
  Serial.begin(9600);
 
  
  BT.begin(38400); 
}

void loop(){
  String h = "hola";
 // Serial.println(h);
  bT();
 
}


int motion = 0;
void bT(){
  
  
      BT.listen();
      while(BT.available()>0){
        String h = "hola";
          char in = BT.read();
          Serial.println(in);
          
          
           
          if(String(in)== "3"){
                changeGear();   
            }

          else if(String(in) == "2"){
            contador = 0;
            //move();
          }
          
          else if(String(in)== "4"){
            analogWrite(gasPWM,250);
            contGas = 250;
           }

           else if(String(in)== "5"){
            analogWrite(gasPWM,0);
            contGas = 0;
           }else{
              turn(in);  
           }
        
           delay(10);
         
      }
           
  }


void changeGear(){
                if(motion == 0){
                  digitalWrite(7,HIGH);
                  digitalWrite(8, HIGH);
                  motion = 1;
  
                }
                else{
                  digitalWrite(7,LOW);
                  digitalWrite(8, LOW);
                  motion = 0;
                }  
}


void move(){
      if(contador >= 45 && contador <= 115 ){
                  servomotor.write(contador);  
                  delay(10);
              }
              
}

void faster(){


    if(contGas <= 200 && contGas){
        
    }
    analogWrite(gasPWM,contGas);
  
  
}



void turn(char deg){
  
      int c_deg = atoi(deg);
      c_deg = c_deg + convertDeg;


      
      if(c_deg > currentDeg){
          if(currentDeg > minDeg && currentDeg < maxDeg){
            currentDeg++;  
          }   
          else{
            correct();     
          }
          
      }
        
         
      
      if(c_deg < currentDeg){
          if(currentDeg > minDeg && currentDeg < maxDeg){
            currentDeg--;
                
            }
           else{ 
              correct();
           }
      
      }
        
      
      
      servomotor.write(currentDeg);
      
}


void correct(){
  if(servomotor.read() <= minDeg){
    for(int i;servomotor.read() <= minDeg;i++){
      servomotor.write(i);
      
    }
    currentDeg = minDeg + 1;
  }
  
  if(servomotor.read() >= maxDeg){
      for(int i;servomotor.read() >= maxDeg;i--){
      servomotor.write(i);
      
    }
      currentDeg = maxDeg - 1;
    }
}


  
