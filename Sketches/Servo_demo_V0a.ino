//Servo_demo_V0a.ino

//Demonstration of AdaFruit PCA9685 16 channel servo driver
//Adafruit product #815 and Miuzei Micro Servos 9g MS18 (metal gears)

//23 Febuary 2025

//James Canova
//jscanova@gmail.com

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver m_PWM;

const int SERVO_FREQ = 50;   //Hz,  // Analog servos run at ~50 Hz updates

// This is the minimum pulse length count (out of 4096) for servos
//corresponds to +90 [deg] (clockwise) accordiong to manufacture's definitions of + angle
const int PULSELEN_MIN  = 105;

// This is the maximum pulse length count (out of 4096)  for servos
//corresponds to -90 [deg] (counter-clockwise) accordiong to manufacture's definitions of + angle
const int PULSELEN_MAX = 477;

float m_nAngle_deg;
float m_nAngleIncement;
int m_nMax;
bool m_bCycleComplete;
bool m_bCentered;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Servo test.");

  m_PWM.begin();
	m_PWM.setPWMFreq(SERVO_FREQ); 

  //center servos 0 and 1
  m_PWM.setPWM(0, 0,  372); 
  m_PWM.setPWM(1, 0,  372);

  m_nAngle_deg = 0.0;
  m_nAngleIncement = 5.0;
  m_nMax = 5;
  m_bCycleComplete = false;
  m_bCentered = false;

}

void loop() {

 // put your main code here, to run repeatedly:
  int nServoNumber; 
  float nPulseLen; 

  if (!m_bCentered) {
    for (nServoNumber = 0; nServoNumber <= 9 ;nServoNumber++)
      {
        m_PWM.setPWM(nServoNumber, 0,  300); 
        delay(250);
      }
      m_bCentered = true;
    }

  m_nAngle_deg = m_nAngle_deg + m_nAngleIncement;

  if (m_nAngle_deg > 35.0) 
    m_nAngleIncement = -m_nAngleIncement;

  if (m_nAngle_deg < -35.0) {
    m_nAngleIncement = -m_nAngleIncement;
    m_bCycleComplete = true;
  }

  if (m_bCycleComplete && m_nAngle_deg == 0.0) {
    m_nMax = m_nMax + 1;
    if (m_nMax > 8) {
      m_nMax = 0;
    }
    m_bCycleComplete = false;
  }

  nPulseLen = ConvertDegToPulseLen(m_nAngle_deg);

  for (nServoNumber = 0; nServoNumber <= m_nMax ;nServoNumber++)
  {
    m_PWM.setPWM(nServoNumber, 0,  nPulseLen);
    Serial.println(nServoNumber); 
    delay(250);
  }

}


//Functions==============================================================

//Degrees is CCW when viewing servo from top
//equation generated experimentally
int ConvertDegToPulseLen(int nDeg)
  {
    int nPulseLen;
	
	  nPulseLen = map(nDeg, -90, 90, PULSELEN_MIN, PULSELEN_MAX);
    
    return nPulseLen;
  }


  //to prevent attempting to drive servo outside +/-90 deg limits
float CheckPulseLenLimits(int nPulseLen)
 {
   if (nPulseLen > PULSELEN_MAX) 
        nPulseLen = PULSELEN_MAX;  
  
     if (nPulseLen < PULSELEN_MIN)
        nPulseLen = PULSELEN_MIN;           

    return nPulseLen;
  }



