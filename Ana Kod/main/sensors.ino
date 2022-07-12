#ifndef _SENSORS_
#define _SENSORS_

initializeSensors()
{
  TCCR0B = TCCR0B & B11111000 | B00000010;

  // Motor
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  rotateMotor(0, 0);

  // Line Following
  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  pinMode(IR_SENSOR_FAR_RIGHT, INPUT);
  pinMode(IR_SENSOR_FAR_LEFT, INPUT);
  pinMode(IR_SENSOR_MIDDLE, INPUT);

  // Distance Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  // Buzzer
  pinMode(buzzer, OUTPUT);
}

static long currentSensorInfo[6];
void GetSensorInfo()
{
  currentSensorInfo[0] = digitalRead(IR_SENSOR_FAR_LEFT);
  currentSensorInfo[1] = digitalRead(IR_SENSOR_LEFT);
  currentSensorInfo[2] = digitalRead(IR_SENSOR_MIDDLE);
  currentSensorInfo[3] = digitalRead(IR_SENSOR_RIGHT);
  currentSensorInfo[4] = digitalRead(IR_SENSOR_FAR_RIGHT);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  currentSensorInfo[5] = distance

      return;
}

#endif