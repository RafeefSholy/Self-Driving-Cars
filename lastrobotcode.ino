#include <ESP32Servo.h>
#include <NewPing.h> //for altrasonic 




const int freq = 5000;
const int pwmMotorRight = 0; //right 
const int pwmMotorLeft = 1; //left
const int resolution = 8; 


#define pressedButton 2
#define SERVO_PIN 14
#define ultra_trigPin 12     //الالتراسونيك  
#define ultra_echoPin 13
#define MAX_DISTANCE 200
#define IN1 19              // L298N ـfor motor1 _left ـتوصيلات البريدج
#define IN2 18
#define ENB 4
#define IN3 17               // for motor 2_right 
#define IN4 16
#define ENA 5    

Servo steeringServo;
bool robotStarted = false;
NewPing sonar(ultra_trigPin ,  ultra_echoPin, MAX_DISTANCE);



void setup() {
pinMode(pressedButton , INPUT_PULLUP);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // PWM للموتورين
  ledcSetup(pwmMotorRight, freq, resolution);
  ledcAttachPin(ENA, pwmMotorRight);
  ledcSetup(pwmMotorLeft, freq, resolution);
  ledcAttachPin(ENB, pwmMotorLeft);

  // إعداد السيرفو
  steeringServo.setPeriodHertz(50);
  steeringServo.attach(SERVO_PIN, 500, 2400);
  steeringServo.write(90); 
 
}


void loop() {
  if (!robotStarted) {
    if (digitalRead(pressedButton ) == LOW) {
      delay(300);  
      robotStarted = true;
    } else {
      return;  
    }
  }

   int distance = sonar.ping_cm();
  // قراءة المسافه,+سيرفو
  if (distance > 0 && distance < 10) {
    steeringServo.write(70); 
  } else if (distance >= 10 && distance < 15) {
    steeringServo.write(80);
  } else if (distance >= 15 && distance <= 30) {
    steeringServo.write(90);
  } else {
    steeringServo.write(100);
  }
  moveForward(220,220);
  delay(50);
}
//  لتحريك الروبوت للأمام
void moveForward(int leftSpeed, int rightSpeed) {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  ledcWrite(pwmMotorRight , rightSpeed);  
  ledcWrite(pwmMotorLeft , leftSpeed);
}

