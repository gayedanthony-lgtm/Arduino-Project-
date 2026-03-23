#include <Servo.h>

//define pins
const int trigPin = 12;
const int echoPin = 11;
const int servoPin = 13;
const int RED_LED_PIN = 7;
const int GREEN_LED_PIN = 6;
// Create servo object
Servo servo;

//variables for the Ultrasonic sensor
float duration;
float distance;  // Use float for better precision

void setup() {
  Serial.begin(115200);

  //configure LED pins
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  //a servo to pin
  servo.attach(servoPin);
  servo.write(53);  // Initial position of the servo. It took a bit of trial and
  //error to find the right angle for the initial position. 53 degrees
  //was the best angle I found so that the servo was parallel to my table.

  //configure ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  //make red light on and green light off
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);

  //send trigger pulse to ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //measure echo duration
  duration = pulseIn(echoPin, HIGH);

  //calculate distance in cm
  distance = (duration * 0.0343) / 2.0;

  //print distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  //control servo based on distance
  if (distance <= 20.0) {
    //makes servo go up, red light turn off and green light 
    //turn on when an object is 20cm or less away from
    //the ultrasonic sensor
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    servo.write(180);
    unsigned long t1 = millis();
while (millis() - t1 < 3000){
  //hold the servo position up and the green light on for 3 seconds
  
}  
  } else {
    //makes servo go/stay down, red light turn/stay on and green light 
    //turn/stay off when an object is further than 20cm away from
    //the ultrasonic sensor
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    servo.write(53);
  }

  delay(100);  //small delay to stabilize readings
}
