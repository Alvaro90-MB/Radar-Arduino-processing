#include <Servo.h>

#define TRIG_PIN 10
#define ECHO_PIN 11
#define SERVO_PIN 12
#define LED1_PIN 5
#define LED2_PIN 6
#define BUZZER_PIN 2

Servo myservo;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  myservo.attach(SERVO_PIN);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  for (int pos = 0; pos <= 180; pos += 1)
  {
    myservo.write(pos);
    delay(15);
    int distance = 0.01723 * readUltrasonicDistance(TRIG_PIN, ECHO_PIN);

    if (distance < 20) {
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      tone(BUZZER_PIN, 1000);
    } else {
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
      noTone(BUZZER_PIN);
    }

    Serial.print(pos);
    Serial.print(",");
    Serial.println(distance);
    Serial.flush();
    delay(100);  
  }
  for (int pos = 180; pos >= 0; pos -= 1)
  {
    myservo.write(pos);
    delay(15);
    int distance = 0.01723 * readUltrasonicDistance(TRIG_PIN, ECHO_PIN);

    if (distance < 20) {
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      tone(BUZZER_PIN, 1000);
    } else {
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
      noTone(BUZZER_PIN);
    }

    Serial.print(pos);
    Serial.print(",");
    Serial.println(distance);
    Serial.flush();
    delay(100);  
  }
}
