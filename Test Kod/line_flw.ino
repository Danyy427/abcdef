#define IR_SENSOR_RIGHT 8
#define IR_SENSOR_LEFT 9
#define MOTOR_SPEED 80

//Right motor
int enableRightMotor=5;
int rightMotorPin1=2;
int rightMotorPin2=3;

//Left motor
int enableLeftMotor=6;
int leftMotorPin1=7;
int leftMotorPin2=4;

//Distance Sensor
const int trigPin = 10;
const int echoPin = 11;

long duration;
int distance;

//Buzzer
const int buzzer = 22;

void setup()
{
  //The problem with TT gear motors is that, at very low pwm value it does not even rotate.
  //If we increase the PWM value then it rotates faster and our robot is not controlled in that speed and goes out of line.
  //For that we need to increase the frequency of analogWrite.
  //Below line is important to change the frequency of PWM signal on pin D5 and D6
  //Because of this, motor runs in controlled manner (lower speed) at high PWM value.
  //This sets frequecny as 7812.5 hz.
  TCCR0B = TCCR0B & B11111000 | B00000010 ;
  
  // put your setup code here, to run once:
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  rotateMotor(0,0);   

  //Distance Sensor
  pinMode(trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  Serial.begin(9600);

  //Buzzer
  pinMode(buzzer, OUTPUT);  
}


void loop()
{
  //Distance Sensor
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;

  Serial.print("Distance: ");
  Serial.println(distance);


  //Motor Motion
  
  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);
  
     if (distance > 20) {
 
            //If none of the sensors detects black line, then go straight
            if (rightIRSensorValue == LOW && leftIRSensorValue == LOW )
            {
              rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
            }
            //If right sensor detects black line, then turn right
            else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW)
            {
                rotateMotor(-MOTOR_SPEED, MOTOR_SPEED); 
            }
            //If left sensor detects black line, then turn left  
            else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH )
            {
                rotateMotor(MOTOR_SPEED, -MOTOR_SPEED); 
            } 
            //If both the sensors detect black line, then stop 
            else 
            {
              rotateMotor(0, 0);
            }
     }
      
      else if (distance <= 20) {
    
              rotateMotor(0, 0);
              // 15 SANİYELİK BEKLEME ESNASINDA İKAZ SESİ ÇALARAK UYARI VERECEK
              tone(buzzer, 432, 250);
              delay(15000);
              noTone(buzzer);
              
              //if (distance <= 20) {
              //EĞER ENGEL DURUYORSA ETRAFINDAN DOLAŞACAK
                //SAĞA GİT 
                //rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
                
                //ÇİZGİYE PARALEL GİT (SOLA DÖN)
                //SOLA DÖN
             // }

              //else if (distance > 20) {
                //NORMAL YOLUNDA DEVAM ETMESİ İÇİN NORMAL KODU EKLEMEYE GEREK VAR MI?
              // }
    
      } 
   
}


void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,LOW);      
  }

  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
  else 
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
}
