// Left Joystick
int LY = A2, LX = A3, LS = 15;
int LY_Values, LX_Values;
bool LS_Position;
// Right Joystick
int RY = A11, RX = A10, RS = 7;
int RY_Values, RX_Values;
bool RS_Position;
  
// Push Buttons
int S1 = 21, S2 = 22, S3 = 2, S4 = 3;
bool S1_Position, S2_Position, S3_Position, S4_Position;

// Toggle Switches
int TL = 13, TR = 12;
bool TL_Position, TR_Position;

// Potentiometers
int PL = A0, PR = A14;
int PL_Values, PR_Values;

// RGB LEDs
int LLR = 18, LLG = 19, LLB = 20;
int LRR = 18, LRG = 19, LRB = 20;
bool LLR_Position, LLG_Position, LLB_Position;
bool LRR_Position, LRG_Position, LRB_Position;

// Camera Servos
int Pan_Servo, Tilt_Servo;

void setup() {
  Serial.begin(9600);
  
  // Left Joystick
  pinMode(LY, INPUT);
  pinMode(LX, INPUT);
  pinMode(LS, INPUT_PULLUP);
  // Right Joystick
  pinMode(RY, INPUT);
  pinMode(RX, INPUT);
  pinMode(RS, INPUT_PULLUP);
  
  // Push Buttons
  pinMode(S1, INPUT_PULLUP);
  pinMode(S2, INPUT_PULLUP);
  pinMode(S3, INPUT_PULLUP);
  pinMode(S4, INPUT_PULLUP);
  
  // Toggle Switches
  pinMode(TL, INPUT_PULLUP);
  pinMode(TR, INPUT_PULLUP);

  // Potentiometers
  pinMode(PL, INPUT);
  pinMode(PR, INPUT);
  
  // RGB LEDs
  pinMode(LLR, OUTPUT);
  pinMode(LLG, OUTPUT);
  pinMode(LLB, OUTPUT);
  pinMode(LRR, OUTPUT);
  pinMode(LRG, OUTPUT);
  pinMode(LRB, OUTPUT);
}

void loop() {

  // Switch between Manual or Automatic Camera control
  if (digitalRead(TL) == HIGH)
  {
    automatic_control();
  }
  else
  {
    manual_control();
  }

}

void manual_control() {
  
}

void automatic_control() {
  // Status LED for Camera control
    digitalWrite(LLR, HIGH);
    
    // Reset other LEDs
    int LEDs[5] = {LLG, LLB, LRR, LRG, LRB};
    for(int x = 0; x <= 4; x++)
    {
      digitalWrite(LEDs[x], LOW);
    }

    // Steering and throttle adjustments
    PL_Values = map(analogRead(PL), 0, 1023, -50, 50);
    PR_Values = map(analogRead(PR), 0, 1023, 0, 180);

    // Collect and Map joystick values to be used for car control
    LY_Values = map(analogRead(LY), 0, 1023, 0, 180) + PL_Values;
    RX_Values = map(analogRead(RX), 0, 1023, 0+PR_Values, 180-PR_Values);

    // Reset Pan/Tilt Servo Positions
    if (digitalRead(S1) == HIGH)
    {
      Pan_Servo = 90;
      Tilt_Servo = 90;
      digitalWrite(LLG, HIGH);
    }
}
