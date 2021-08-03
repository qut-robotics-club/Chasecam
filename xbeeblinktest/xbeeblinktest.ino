int on = 0;

void setup() {
  Serial.begin(9600);
  

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}


void loop() {
  
  
  if (Serial.available()) {
    on = Serial.read();

    if (on == 1){
      digitalWrite(13, HIGH);
    }
    else{
      digitalWrite(13, LOW);
    }
  }
  else
  {
    if (digitalRead(13) == LOW)
    {
      digitalWrite(13, HIGH);
    }
    else 
    {
      digitalWrite(13, LOW);
    }    
  }
  delay(100);
}
