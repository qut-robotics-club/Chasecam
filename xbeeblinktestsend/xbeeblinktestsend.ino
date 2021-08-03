void setup() {
  Serial.begin(9600);
  //int on = 0;
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop() {
  if (digitalRead(2) == LOW) {
    digitalWrite(13, HIGH);
    Serial.print('~');
    Serial.print(0x01);
  } 
  else {
    digitalWrite(13, LOW);
    Serial.print('~');
    Serial.print(0x00);
  }
  delay(50);
}
