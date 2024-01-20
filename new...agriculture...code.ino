#define BLYNK_TEMPLATE_ID "TMPL32M5mpFP2"
#define BLYNK_TEMPLATE_NAME "agriculture car"
#define BLYNK_AUTH_TOKEN "T7YjoneU9MzIaEekJZeDd0cgSyagruaI"
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h> 

// WiFi Car Configuration
#define BLYNK_PRINT Serial
#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5

bool forward = false;
bool backward = false;
bool left = false;
bool right = false;
bool servoControl = false;

char auth[] = "T7YjoneU9MzIaEekJZeDd0cgSyagruaI";  
char ssid[] = "Gaurav";      
char pass[] = "gauravraj";   


Servo myServo; 

void setup() {
  Serial.begin(9600);

  // Motor setup
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  myServo.attach(D7);  


  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V0) {
  forward = param.asInt();
}

BLYNK_WRITE(V1) {
  backward = param.asInt();
}

BLYNK_WRITE(V2) {
  left = param.asInt();
}

BLYNK_WRITE(V3) {
  servoControl = param.asInt();
}

BLYNK_WRITE(V5) {
  right = param.asInt();
}

void loop() {
  Blynk.run();
  smartcar();
  rotateServo();
}

void smartcar() {
  if (forward) {
    Forward();
    Serial.println("Forward");
  } else if (backward) {
    Backward();
    Serial.println("Backward");
  } else if (left) {
    Left();
    Serial.println("Left");
  } else if (right) {
    Right();
    Serial.println("Right");
  } else {
    Stop();
    Serial.println("Stop");
  }
}

void rotateServo() {
  if (servoControl) {
    for (int angle = 0; angle <= 180; angle += 5) {
      myServo.write(angle);
      delay(1);
    }

    delay(1);

    for (int angle = 180; angle >= 0; angle -= 5) {
      myServo.write(angle);
      delay(1);
    }
  }
}


void Forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Backward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void Left() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
