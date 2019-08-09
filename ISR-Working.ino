unsigned long onTime = 10; //amount of time light stays on after trigger
unsigned long triggerTime = 0; //time prop falling edge is detected
unsigned long currentTime = millis();

void setup() {
attachInterrupt(digitalPinToInterrupt(2), blink, FALLING);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(LED_BUILTIN, OUTPUT);

digitalWrite(3, HIGH);
digitalWrite(4, HIGH);
digitalWrite(LED_BUILTIN, LOW);

Serial.begin(9600);

}

void loop() {

currentTime = millis();

  if((currentTime - triggerTime) > onTime){
    digitalWrite(LED_BUILTIN, LOW);
  }
Serial.print("currentTime "); Serial.println(currentTime);
Serial.print("triggerTime "); Serial.println(triggerTime);

}

void blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  triggerTime = millis();
}
