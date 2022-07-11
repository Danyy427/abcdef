#include "D:/abcdef/Ana Kod/main/pins.ino"

#ifndef _MOVE_
#define _MOVE_

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{

  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }
  else
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }
  else
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}

void goForward()
{
  rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
}

void turnRight()
{
  rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
}

void turnLeft()
{
  rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
}

void stopMoving()
{
  rotateMotor(0, 0);
}

void goBackward()
{
  rotateMotor(-MOTOR_SPEED, -MOTOR_SPEED);
}

#endif
