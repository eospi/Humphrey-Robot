//Pin to trigger driver
int STBY = 10;

//Motor A Pins
int PWMA = 3;
int AIN1 = 9;
int AIN2 = 8;

//Motor B Pins
int PWMB = 5;
int BIN1 = 11;
int BIN2 = 12;

// Joystick Pins
int VERTICALPIN = A0;
int HORIZONTALPIN = A2;
int vertical;
int horizontal;

// Speed and direction variables
int spd;
String dir;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(STBY, OUTPUT);
  
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  mapAndConstrain(); // Converts analog readings to 8-bit int for PWM
  findDirection(); // Finds direction of joystick
  moveRobot(); // Move the robot

  Serial.println(dir);
  Serial.println(spd);

  delay(2);
}

void mapAndConstrain() {
  vertical = analogRead(VERTICALPIN);
  horizontal = analogRead(HORIZONTALPIN);
  
  vertical = map(vertical, 0, 1023, -255, 255);
  vertical = constrain(vertical, -255, 255);

  horizontal = map(horizontal, 0, 1023, -255, 255);
  horizontal = constrain(horizontal, -255, 255);
}

void findDirection() {  
  if (vertical > -20) {
    dir = "Backwards";
    spd = vertical;
  }
  else if (vertical < 20) {
    dir = "Forwards";
    spd = vertical;
  }

  if (horizontal < -20) {
    dir = "Left";
    spd = horizontal;
  }
  else if (horizontal > 20) {
    dir = "Right";
    spd = horizontal;
  }  

  if (vertical < 20 && vertical > -20 && horizontal < 20 && horizontal > -20) {
    dir = "Stop";
    spd = 0; 
  }

  if (spd < 0) {
    spd = spd * -1;
  }
}

void moveRobot() {
  if (dir == "Forwards") {
    move(0, spd, 0);
    move(1, spd, 0);
  }

  if (dir == "Backwards") {
    move(0, spd, 1);
    move(1, spd, 1);
  }

  if (dir == "Left") {
    move(0, 200, 0);
    move(1, 200, 1);
  }

  if (dir == "Right") {
    move(0, 200, 1);
    move(1, 200, 0);
  }
  
  if (spd == 0) {
    move(0, 0, 0);
    move(1, 0, 0);
  }
}

void move(int motor, int speed, int direction)
{
  // Motor: B = 0, A = 1
  // Speed: 0-255
  // Direction: Clockwise = 0, Counter-clockwise = 1
  
  // Start driver
  digitalWrite(STBY, HIGH);
  
  // Set direction to default
  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;
  
  // Change direction if different
  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }
  
  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }
  else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}




