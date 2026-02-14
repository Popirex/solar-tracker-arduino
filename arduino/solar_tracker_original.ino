#include <Servo.h>
#define SENS1 A0
#define SENS2 A2

Servo servo;
int gradi = 45;
int val_1_sens_1;
int val_1_sens_2;
int val_2_sens_1;
int val_2_sens_2;
int media_sensore1;
int media_sensore2;
int indice = 1;

void setup() {
  servo.attach(6);
  Serial.begin(9600);
  pinMode(SENS1, INPUT);
  pinMode(SENS2, INPUT);
  servo.write(0);
  delay(500);
  servo.write(90);
  delay(500);
  servo.write(45);
  delay(500);
}

void loop() {
    val_1_sens_1 = val_2_sens_1;
    val_1_sens_2 = val_2_sens_2;
    val_2_sens_1 = (analogRead(SENS1))/50;
    val_2_sens_2 = (analogRead(SENS2) - 5)/50;

    media_sensore1 = (val_1_sens_1 + val_2_sens_1) /2;
    media_sensore2 = (val_1_sens_2 + val_2_sens_2) /2;
    Serial.println(gradi);
    
   if(media_sensore1 > media_sensore2 && gradi-1 >=0){
    gradi--;
    servo.write(gradi);
   }
   if(media_sensore1 < media_sensore2 && gradi+1 <=90){
    gradi++;
    servo.write(gradi);
   }
}
