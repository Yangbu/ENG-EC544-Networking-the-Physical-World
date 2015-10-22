#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3); // RX, TX
int sensorPin = A0;
long Rth;   //the resistence of the thermistor
double Temp; //the temperature of the environment
int i; // the loop number
double sum; 
double sensorVal;  // the analog value input from arduino

void setup() {
  // put your setup code here, to run once:
  // add
  XBee.begin(9600);
  Serial.begin(9600);
  pinMode(A0, INPUT); //read the analog value input from PIN A0
  i = 0;
  sum = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorVal = analogRead(A0);
  Rth = ((10240000/sensorVal) - 10000); 
  Temp = log(Rth);
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;
  sum += Temp;
  i++;
  //Serial.print("sum:");
  //Serial.println(sum);
  //output the average temp every 10s
  if(i==10){
    Serial.print("A Temp:");
    Serial.println(sum/10);
    XBee.print("A Temp:");
    XBee.println(sum/10);
    i = 0;
    sum = 0;
    delay(3000);
  }
  
  
}

