#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "DHT.h"

Adafruit_MPU6050 mpu;
DHT dht(4, DHT22);

float currentSpeed = 0.0;
float maxSpeed = 50.0;
float minSpeed = 0.0;
int gear = 1;
const float accSpeed = 0.8;
const float decSpeed = 0.3;
bool gasPedalPressed = false;
unsigned long lastInputTime = 0;
float lastSpeed = -1.0;
int lastGear = -1;

bool accelerate = false, stop = false, doIHonk = false;
int lastGearUpState = HIGH;
int lastGearDownState = HIGH;

const int accButtonPin = 23;
int accButton = 0;
const int brkButtonPin = 22;
int brkButton = 0;
const int HOOONKPin = 21;
int HOOONK = 0;
const int gearUpButtonPin = 20;
int gearUpButton;
const int gearDownButtonPin = 19;
int gearDownButton;

const int switchModeButtonPin = 18;
int switchModeButton = 0;
int mode = 0;
int lastSwitchState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode (accButtonPin, INPUT_PULLUP);
  pinMode (brkButtonPin, INPUT_PULLUP);
  pinMode (HOOONKPin, INPUT_PULLUP);
  pinMode(gearUpButtonPin, INPUT_PULLUP);
  pinMode (gearDownButtonPin, INPUT_PULLUP);
  pinMode (switchModeButtonPin, INPUT_PULLUP);
  pinMode(8, OUTPUT); 
  Serial.println("Simulator Initialized. System Ready.");

  Wire.begin(5, 6);
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  dht.begin();
}

void loop() {

  accButton = digitalRead(accButtonPin);
  brkButton = digitalRead(brkButtonPin);
  HOOONK = digitalRead(HOOONKPin);
  gearUpButton = digitalRead(gearUpButtonPin);
  gearDownButton = digitalRead(gearDownButtonPin);
  switchModeButton = digitalRead(switchModeButtonPin);

  if (switchModeButton == LOW && lastSwitchState == HIGH) {
    if (mode == 0) {
      mode = 1;
      Serial.println("--- MODE: MEASUREMENT ---");
    } else {
      mode = 0;
      Serial.println("--- MODE: ACCELERATION ---");
    }
    delay(50);
  }
  lastSwitchState = switchModeButton;

  if (mode == 0) {
    uint8_t data = 0;

    accelerate = false;
    stop = false;
    doIHonk = false;

    if (accButton == LOW) {
      gasPedalPressed = true;
      lastInputTime = millis();
      accelerate = true;
    }

    if (brkButton == LOW) {
      currentSpeed -= (decSpeed * 10.0);
      stop = true;
    }

    if (HOOONK == LOW) {
      doIHonk = true;
    }

    int oldGear = gear;
    
    if (gearUpButton == LOW && lastGearUpState == HIGH) {
      if (gear < 7) gear++;
    }
    lastGearUpState = gearUpButton;

    if (gearDownButton == LOW && lastGearDownState == HIGH) {
      if (gear > 1) gear--;
    }
    lastGearDownState = gearDownButton;

    if (oldGear != gear) {
      switch (gear) {
        case 1: minSpeed = 0.0;   maxSpeed = 50.0;  break;
        case 2: minSpeed = 30.0;  maxSpeed = 80.0;  break;
        case 3: minSpeed = 60.0;  maxSpeed = 110.0; break;
        case 4: minSpeed = 90.0;  maxSpeed = 170.0; break;
        case 5: minSpeed = 100.0; maxSpeed = 230.0; break;
        case 6: minSpeed = 150.0; maxSpeed = 300.0; break;
        case 7: minSpeed = 200.0; maxSpeed = 450.0; break;
      }
      /*
      Serial.print("--- SHIFTED TO GEAR ");
      Serial.print(gear);
      Serial.println(" ---");
      */

    }

    if (millis() - lastInputTime > 200) {
      gasPedalPressed = false;
    }

    if (gasPedalPressed) {
      currentSpeed += accSpeed;
    } else if (currentSpeed > minSpeed) {
      currentSpeed -= decSpeed;
    }

    if (currentSpeed < minSpeed) {
      currentSpeed += (accSpeed * 1.5); 
    }

    currentSpeed = constrain(currentSpeed, 0.0, maxSpeed);

    /*
    if (accelerate || stop) {
      Serial.print("Gear: ");
      Serial.print(gear);
      Serial.print(stop ? " [BRAKING]" : " [ACCEL]");
      Serial.print(" | Speed: ");
      Serial.println(currentSpeed);
    }

    if (doIHonk) {
      Serial.println("[ HOOOOOOONK ]");
    }
    */

    data |= (accelerate &  0x01);
    data |= ((stop & 0x01) <<1);
    data |= ((doIHonk & 0x01) << 2);
    data |= ((gear & 0x07) << 3);

    Serial.write(data);

  } else if (mode == 1) {
    sensors_event_t a, g, te;
    mpu.getEvent(&a, &g, &te);

    Serial.printf("A:%.2f,%.2f,%.2f | G:%.2f,%.2f,%.2f\n", 
    a.acceleration.x, a.acceleration.y, a.acceleration.z,
    g.gyro.x, g.gyro.y, g.gyro.z);

    static unsigned long lastDHTRead = 0;
    static float lastTemp = 0;
    
    if (millis() - lastDHTRead > 2000) {
      float temp = dht.readTemperature();
      if (!isnan(temp)) {
        lastTemp = temp;
      }
      lastDHTRead = millis();
    }

    Serial.print("| Temp: ");
    if (lastTemp == 0) Serial.println("Waiting...");
    else Serial.println(lastTemp);
  }

  delay(50);

}