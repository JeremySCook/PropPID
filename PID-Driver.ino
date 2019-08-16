#include <PID_v1.h>

char receivedChar;
boolean newData = false;

unsigned long changeTime = 0; //last time the sensor was triggered
volatile unsigned long quarterSpins = 0;
unsigned long currentTime = millis();
double driverOut = 220;
double difference = 10;
double setPoint = 10;
String inString;
int Kp = 3;
int Ki = 2;
int Kd = 1;

PID myPID(&difference, &driverOut, &setPoint,Kp,Ki,Kd, DIRECT);

void setup() {

myPID.SetMode(AUTOMATIC);

attachInterrupt(digitalPinToInterrupt(2), blink, CHANGE);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(LED_BUILTIN, OUTPUT);

digitalWrite(3, HIGH);
digitalWrite(4, HIGH);
digitalWrite(LED_BUILTIN, LOW);

Serial.begin(9600);

}

void loop() {
myPID.Compute();
analogWrite(3, driverOut);
Serial.print("  difference: "); Serial.print(difference); Serial.print("  ");
Serial.print("setPoint: "); Serial.print(setPoint); Serial.print("  ");
Serial.print("driverOut: "); Serial.println(driverOut);
digitalWrite(LED_BUILTIN, LOW);
recvOneChar();
showNewData();

}

void blink() {
quarterSpins++;
currentTime = millis();
difference = currentTime - changeTime;
changeTime = currentTime;

digitalWrite(LED_BUILTIN, HIGH);
}

void recvOneChar() {
 if (Serial.available() > 0) {
 receivedChar = Serial.read();
 newData = true;
 }
}

void showNewData() {
 if (newData == true) {
 if (isDigit(receivedChar)) {
 inString += (char)receivedChar;}
 if (receivedChar == '\n') {
 setPoint = (inString.toInt());
 inString = "";
 newData = false;
 }
}
}
