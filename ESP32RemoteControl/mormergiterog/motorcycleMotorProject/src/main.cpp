#include <Arduino.h>

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

void setup() {
    Serial.begin(115200);
    pinMode(8, OUTPUT); 
    Serial.println("Simulator Initialized. System Ready.");
}

void loop() {
    if (Serial.available() > 0) {
        char k = Serial.read();

        if (k == 'w' || k == 'W') {
            gasPedalPressed = true;
            lastInputTime = millis();
        }

        if (k == 's' || k == 'S') {
            currentSpeed -= (decSpeed * 10.0);
        }

        if (k == 'h' || k == 'H') {
            Serial.println("\n[ HOOOOOOONK ]");
        }

        int oldGear = gear;
        if ((k == 'q' || k == 'Q') && gear > 1) gear--;
        if ((k == 'e' || k == 'E') && gear < 5) gear++;

        if (oldGear != gear) {
            switch (gear) {
                case 1: minSpeed = 0.0;   maxSpeed = 50.0;  break;
                case 2: minSpeed = 30.0;  maxSpeed = 80.0;  break;
                case 3: minSpeed = 60.0;  maxSpeed = 110.0; break;
                case 4: minSpeed = 90.0;  maxSpeed = 170.0; break;
                case 5: minSpeed = 100.0; maxSpeed = 230.0; break;
            }
        }
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

    if ((int)currentSpeed != (int)lastSpeed || gear != lastGear) {
        Serial.print("Gear: ");
        Serial.print(gear);
        Serial.print(" | Speed: ");
        Serial.println(currentSpeed);
        
        lastSpeed = currentSpeed;
        lastGear = gear;
    }

    digitalWrite(8, gasPedalPressed);
    
    delay(50);
}