//Stepper_motor_V0a.ino

//Modified version of sketch written by ChatGPT

//12 March 2025

//James Canova
//jscanova@gmail.com

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


#define STEP_CHANNEL 0     // m_PWM9685 Channel for STEP signal
#define DIR_PIN 2          // Connected to DIR pin on expansion board
#define ENABLE_PIN 3       // Optional: Connected to ENABLE pin on expansion board (LOW = enabled)

Adafruit_PWMServoDriver m_PWM;

void setup() {
    Serial.begin(9600);
    Wire.begin();

    m_PWM.begin();
    m_PWM.setPWMFreq(1000);  // Set PWM frequency [Hz] to 1.6 kHz (max reliable rate)

    pinMode(DIR_PIN, OUTPUT);
    pinMode(ENABLE_PIN, OUTPUT);
    
    digitalWrite(DIR_PIN, HIGH);   // Set initial direction
    digitalWrite(ENABLE_PIN, LOW); // Enable the driver
    delay(100);
}


void loop() {

    Serial.println("Moving Forward");
    digitalWrite(DIR_PIN, HIGH);  // Forward direction
    stepMotor(20, 50);          // Move 200 steps (1 revolution at full step)
    delay(10);

    Serial.println("Moving Backward");
    digitalWrite(DIR_PIN, LOW);  // Reverse direction
    stepMotor(20, 50);
    delay(10);

}


//Function
void stepMotor(int steps, int delayMicroseconds) {
    for (int i = 0; i < steps; i++) {
        m_PWM.setPWM(STEP_CHANNEL, 0, 2048);  // High pulse
        delay(delayMicroseconds);
        m_PWM.setPWM(STEP_CHANNEL, 0, 0);     // Low pulse
        delay(delayMicroseconds);
    }
}