// Left Joystick X, Y and Switch
int LY = A2, LX = A3, LS = 15;
int LY_Values, LX_Values;
bool LS_Position;
// Right Joystick X, Y and Switch
int RY = A11, RX = A10, RS = 7;
int RY_Values, RX_Values;
bool RS_Position;

// Push Buttons: S1= reset camera, S2-S4=unused
int S1 = 21, S2 = 22, S3 = 2, S4 = 3;
bool S1_Position, S2_Position, S3_Position, S4_Position;

// toggle switches: TL= On/off, TR= Manual/Auto
int TL = 13, TR = 12;
bool TL_Position, TR_Position;

// Potentiometers input=0-1023: PL= steering adjustment, PR= throttle adjustment
int PL = A0, PR = A14;
int PL_Values, PR_Values;

// Left RGB LEDs:
// red= Power on but no control
// blue= Power on and in Manual Mode
// green= Power on and in Automatic Mode
int LLR = 18, LLG = 19, LLB = 20;

// RIGHT RGB LEDs:
// blinks red=Camera Servo positions reset
int LRR = 18, LRG = 19, LRB = 20;
bool LLR_Position, LLG_Position, LLB_Position;
bool LRR_Position, LRG_Position, LRB_Position;

// Camera Servos pan(LEFT/RIGHT), tilt(UP/DOWN)
int Pan_Servo, Tilt_Servo;

// Throttle and steering
int Throttle, Steering;

void setup()
{
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

void loop()
{
  reset_leds()

      // On/OFF
      if (digitalRead(TL) == HIGH)
  {
    // Switch between Manual or Automatic Camera control
    if (digitalRead(TR) == HIGH)
    {
      automatic_control();
    }
    else
    {
      manual_control();
    }
  }
  else
  {
    reset();
    LLR_Position = 1;
  }
  set_leds()
}

void reset()
{
  int LY_Values, LX_Values = 90;
  bool LS_Position = 0;
  int RY_Values, RX_Values = 90;
  bool RS_Position = 0;
  bool S1_Position, S2_Position, S3_Position, S4_Position = 0;
  bool TL_Position, TR_Position = 0;
  int PL_Values, PR_Values = 90;
  bool LLR_Position, LLG_Position, LLB_Position = 0;
  bool LRR_Position, LRG_Position, LRB_Position = 0;
  int Pan_Servo, Tilt_Servo = 90;
  int Throttle, Steering = 0;
}

void reset_camera()
{
  Pan_Servo = 90;
  Tilt_Servo = 90;
  LRR_Position = 1;
}


void reset_leds()
{
  bool LLR_Position, LLG_Position, LLB_Position = 0;
  bool LRR_Position, LRG_Position, LRB_Position = 0;
  int LEDs[6] = {LLR, LLG, LLB, LRR, LRG, LRB};
  for (int x = 0; x < 6; x++)
  {
    digitalWrite(LEDs[x], LOW);
  }
}


void set_leds()
{
  int LED_positions[6] = {LLR_Position, LLG_Position, LLB_Position, LRR_Position, LRG_Position, LRB_Position};
  int LEDs[6] = {LLR, LLG, LLB, LRR, LRG, LRB};
  for (int x = 0; x < 6; x++)
  {
    digitalWrite(LEDs[x], LED_positions[x] * HIGH);
  }
}

// In manual mode:
// left joystick up/down is throttle and left/right is steering.
// Right joystick up/down is camera tilt (up/down) and left/right is camera pan (left/right).
void manual_control()
{
  // set left blue led on
  LLB_Position = 1;

  // Collect and Map Pententiometer values for Steering and throttle adjustments
  PL_Values = map(analogRead(PL), 0, 1023, -50, 50);
  PR_Values = map(analogRead(PR), 0, 1023, 0, 180);

  // Collect and Map left joystick x and y
  LX_Values = map(analogRead(LX), 0, 1023, 0, 180);
  LY_Values = map(analogRead(LY), 0, 1023, 0, 180);

  // Collect and Map right joystick x and y
  RX_Values = map(analogRead(RX), 0, 1023, 0, 180);
  RY_Values = map(analogRead(RY), 0, 1023, 0, 180);

  // map joystick values to throttle and steering, with adjustments
  Throttle = map(LY_Values, 0, 180, 0 + PR_Values, 180 - PR_Values);
  Steering = LX_Values + PL_Values;
  Pan_Servo = RX_Values;
  Tilt_Servo = RY_Values;

  // Reset Pan/Tilt Servo Positions
  if (digitalRead(S1) == HIGH)
  {
    reset_camera()
  }
}

// In automatic mode:
// left joystick up/down is throttle and right joystick left/right is steering.
void automatic_control()
{
  // set left green led on
  LLG_Position = 1;

  // Collect and Map Pententiometer values for Steering and throttle adjustments
  PL_Values = map(analogRead(PL), 0, 1023, -50, 50);
  PR_Values = map(analogRead(PR), 0, 1023, 0, 180);

  // Collect and Map left joystick x and y
  LX_Values = map(analogRead(LX), 0, 1023, 0, 180);
  LY_Values = map(analogRead(LY), 0, 1023, 0, 180);

  // Collect and Map right joystick x and y
  RX_Values = map(analogRead(RX), 0, 1023, 0, 180);
  RY_Values = map(analogRead(RY), 0, 1023, 0, 180);

  // map joystick values to throttle and steering, with adjustments
  Throttle = map(LY_Values, 0, 180, 0 + PR_Values, 180 - PR_Values);
  Steering = RX_Values + PL_Values;
  Pan_Servo = 90;
  Tilt_Servo = 90;

  // Reset Pan/Tilt Servo Positions
  if (digitalRead(S1) == HIGH)
  {
    reset_camera()
  }
}
