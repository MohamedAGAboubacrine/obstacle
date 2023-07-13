const int TRIG_PIN = 6;        // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN = 7;        // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int pin_PWM = 3;         // Arduino pin connected to Piezo Buzzer's pin
int DISTANCE_THRESHOLD = 100;  // centimeters
                               // variables will change:
float duration_us, distance_cm;
int vibration = 0;


void setup() {
  Serial.begin(9600);         // initialize serial port
  pinMode(TRIG_PIN, OUTPUT);  // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);   // set arduino pin to input mode
  pinMode(pin_PWM, OUTPUT);   // set arduino pin to output
  analogWrite(pin_PWM, 150); 
  delay((200));
  analogWrite(pin_PWM, 0);
  delay(100);
  analogWrite(pin_PWM, 150);
  delay((200));
  analogWrite(pin_PWM, 0); 


}
                   
void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;
  if (distance_cm < DISTANCE_THRESHOLD && distance_cm > 50) {
    vibration = map(distance_cm, 50, 100, 255, 150);
    Serial.print(vibration);
    analogWrite(pin_PWM, vibration);  //
  } else if (distance_cm <= 50) analogWrite(pin_PWM, 255);

  else {
    analogWrite(pin_PWM, 0);
  }


  // print the value to Serial Monitor
  Serial.print("  ");
  Serial.println(distance_cm);
  //Serial.println(" cm");



  delay(10);
}