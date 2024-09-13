

#include <Dabble.h>

#include <Servo.h>   //Runs the PWM for the ESC
Servo ESC;          // Create servo object to control the ESC

#include <SparkFun_TB6612.h> // Motor Driver Library provided by Sparkfun

//Left Wheel is Motor A on the PCB
#define L_Wheel_in1 A5  //A4
#define L_Wheel_in2 A4  //A5
#define L_Wheel_PWM 11  //D11

//Left Wheel is Motor B on the PCB
#define R_Wheel_in1 4   //D4
#define R_Wheel_in2 8   //D8
#define R_Wheel_PWM 10  //D10

const int motor_offset = -1;
#define STBY 2
Motor L_Wheel(L_Wheel_in1, L_Wheel_in2, L_Wheel_PWM, motor_offset, STBY);
Motor R_Wheel(R_Wheel_in1, R_Wheel_in2, R_Wheel_PWM, motor_offset, STBY);

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE


void setup() {

  Serial.begin(250000);       // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600, 0, 1);   //(Baudrate, rx,tx) Enter baudrate of your bluetooth. Connect bluetooth on Bluetooth port present on evive (in Dabble Library Example).
  ESC.attach(5, 1000, 2000);  // Initializes the ESC  ---- Pin 5 = ESC A; Pin 6 = ESC B 
  ESC.write(0);               // Sets the speed to 0
}

void loop() {
  Dabble.processInput();      //this function is used to refresh data obtained from smartphone. Hence calling this function is mandatory in order to get data properly from your mobile.

  //Motion Control
  if (GamePad.isUpPressed())  //Move forward
  {
    L_Wheel.drive(255);
    R_Wheel.drive(-255);
  }
  else if (GamePad.isDownPressed()) //Move backward
  {
    L_Wheel.drive(-255);
    R_Wheel.drive(255);
  }
  else if (GamePad.isLeftPressed()) { //Move left
    L_Wheel.drive(-255);
    R_Wheel.drive(-255);
  }
  else if (GamePad.isRightPressed()) { //Move right
    L_Wheel.drive(255);
    R_Wheel.drive(255);
  }
  else {  //Idle
    L_Wheel.drive(0);
    R_Wheel.drive(0);
  }

  //Competition Attachment (Weapon) Control
  if (GamePad.isTrianglePressed())  //Start up the Competition attachment
  {
    ESC.write(35);
    Serial.print("Triangle");
  }
  if (GamePad.isCirclePressed())  //Increase the speed of the competition attachment
  {
    ESC.write(60);
    Serial.print("Circle");
  }
  if (GamePad.isCrossPressed()) //Shut off the competition attachment
  {
    ESC.write(0);
    Serial.print("Cross");
  }

  if (GamePad.isStartPressed()) //Idle
  {

    Serial.print("Start");
    delay(100);
  }

  delay(100);

}