int enA = 32;
int in1 = 33;
int in2 = 25;

void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
  // Configure the timer for PWM on the enA pin
  ledcSetup(0, 5000, 8); // Channel 0, 5000 Hz, 8-bit resolution
  ledcAttachPin(enA, 0); // Attach enA pin to Channel 0
}

void loop() {
  directionControl();
}

// This function lets you control the spinning direction of the motors
void directionControl() {
  // Set the motor speed using PWM
  ledcWrite(0, 120); // Channel 0, 100 (duty cycle)
  
  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}