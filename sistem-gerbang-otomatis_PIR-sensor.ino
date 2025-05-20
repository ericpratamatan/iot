#define BLYNK_TEMPLATE_ID "TMPL6YbtuRrU9"
#define BLYNK_TEMPLATE_NAME "gatenotification"
#define BLYNK_AUTH_TOKEN "CdpHou26lv-whHPnXNy76-UmFGb2wBB0"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Servo.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "sebelah";
char pass[] = "123456789";

#define pirPin D5
BlynkTimer timer;

#define servoPin D7

const int greenLED = D0;
const int redLED = D4;

Servo myServo;

void gateNotification() {
  int isGateAlert = digitalRead(pirPin);
  Serial.println(isGateAlert);
  if (isGateAlert == 1) {
    Serial.println("Gate Open");
    Blynk.logEvent("gate_notification", "Gate Open");
  }
}

void setup() {
  pinMode(pirPin, INPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);

  myServo.attach(servoPin, 500, 2400);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L,gateNotification); 
}

void loop() {
  int motionDetected = digitalRead(pirPin);

  if (motionDetected == HIGH) {
    myServo.write(180);
    Serial.println("Gerakan terdeteksi - Pintu terbuka");
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    delay(8000);
  } else {
    myServo.write(0);
    Serial.println("Tidak ada gerakan - Pintu tertutup");
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    delay(2000);
  }

    Blynk.run();
    timer.run();
}

