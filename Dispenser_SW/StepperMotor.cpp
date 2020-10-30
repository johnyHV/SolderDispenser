/**
   @file StepperMotor.cpp

   @brief Ovladanie krokoveho motora

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#include "StepperMotor.h"

int MotorSteps = 0;
uint16_t MotorSleep = 0;
uint8_t MotorAutoPull = MOTOR_STOP;
uint8_t MotorAutoPullEn = M_A_PULL_E;

/**

   @info Inicializacia motora
   @param none
   @return none
*/
void MotorInit() {
  pinMode(MOTOR_M1, OUTPUT);
  pinMode(MOTOR_M2, OUTPUT);
  pinMode(MOTOR_M3, OUTPUT);
  pinMode(MOTOR_M4, OUTPUT);
}

/**

   @info Nastavenie rychlosti spinania cievok
   @param uint16_t - rychlost v uS
   @return none
*/
void MotorSetSleep(uint16_t val) {
  MotorSleep = val;
}

/**

   @info Ziskam aktualnu medzeru medzi krokmi v uS
   @param none
   @return uint16_t - rychlost v uS
*/
uint16_t MotorGetSleep() {
  return MotorSleep;
}

/**

   @info Funkcia pre spinanie cievok krokoveho motora
   @param uint8_t - smer motora
   @return none
*/
void MotorStepper(uint8_t Direction) {
  switch (MotorSteps) {
    case 0:
      digitalWrite(MOTOR_M1, LOW);
      digitalWrite(MOTOR_M2, LOW);
      digitalWrite(MOTOR_M3, LOW);
      digitalWrite(MOTOR_M4, HIGH);
      break;
    case 1:
      digitalWrite(MOTOR_M1, LOW);
      digitalWrite(MOTOR_M2, LOW);
      digitalWrite(MOTOR_M3, HIGH);
      digitalWrite(MOTOR_M4, HIGH);
      break;
    case 2:
      digitalWrite(MOTOR_M1, LOW);
      digitalWrite(MOTOR_M2, LOW);
      digitalWrite(MOTOR_M3, HIGH);
      digitalWrite(MOTOR_M4, LOW);
      break;
    case 3:
      digitalWrite(MOTOR_M1, LOW);
      digitalWrite(MOTOR_M2, HIGH);
      digitalWrite(MOTOR_M3, HIGH);
      digitalWrite(MOTOR_M4, LOW);
      break;
    case 4:
      digitalWrite(MOTOR_M1, LOW);
      digitalWrite(MOTOR_M2, HIGH);
      digitalWrite(MOTOR_M3, LOW);
      digitalWrite(MOTOR_M4, LOW);
      break;
    case 5:
      digitalWrite(MOTOR_M1, HIGH);
      digitalWrite(MOTOR_M2, HIGH);
      digitalWrite(MOTOR_M3, LOW);
      digitalWrite(MOTOR_M4, LOW);
      break;
    case 6:
      digitalWrite(MOTOR_M1, HIGH);
      digitalWrite(MOTOR_M2, LOW);
      digitalWrite(MOTOR_M3, LOW);
      digitalWrite(MOTOR_M4, LOW);
      break;
    case 7:
      digitalWrite(MOTOR_M1, HIGH);
      digitalWrite(MOTOR_M2, LOW);
      digitalWrite(MOTOR_M3, LOW);
      digitalWrite(MOTOR_M4, HIGH);
      break;
    default:
      digitalWrite(MOTOR_M1, LOW);
      digitalWrite(MOTOR_M2, LOW);
      digitalWrite(MOTOR_M3, LOW);
      digitalWrite(MOTOR_M4, LOW);
      break;
  }
  SetDirection(Direction);
  delayMicroseconds(MotorSleep);
}

/**

   @info Vypnutie krokoveho motora
   @param none
   @return none
*/
void MotorOff() {
  digitalWrite(MOTOR_M1, LOW);
  digitalWrite(MOTOR_M2, LOW);
  digitalWrite(MOTOR_M3, LOW);
  digitalWrite(MOTOR_M4, LOW);
}

/**

   @info Nastavenie smeru otacania motora
   @param int - smer
   @return none
*/
void SetDirection(uint8_t Direction) {

  if (Direction == MOTOR_PUSH) {
    MotorSteps--;
  }
  if (Direction == MOTOR_PULL) {
    MotorSteps++;
  }

  if (MotorSteps > 7) {
    MotorSteps = 0;
  }
  if (MotorSteps < 0) {
    MotorSteps = 7;
  }
}

/**

   @info efekt automaticke povytiahnutia piestu, aby sa netlacila stale pasta
   @param none
   @return none
*/
void MotorAutoPullEffect() {
  
  if (MotorAutoPullEn == true) {
    Serial.println("Enable");
    uint16_t LastSpeed = MotorGetSleep();

    MotorSetSleep(M_A_PULL_SP);
    for (uint8_t i = 0; i <= M_A_PULL_ST; i++) {
      Serial.println(i);
      MotorStepper(MOTOR_PULL);
    }

    MotorOff();
    MotorSetSleep(LastSpeed);
  } else {
    Serial.println("Disable");
  }
  
  
  MotorAutoPull = MOTOR_STOP;
}

/**

   @info Nastavenie auto pull efektu cez mode button
   @param status modu
   @return none
*/
void MotorAutoPullEnDis(uint8_t input) {
  Serial.print("Pull status: ");
  Serial.println(input);
  MotorAutoPullEn = input;
}

uint8_t MotorAutoPullStatus() {
  return MotorAutoPullEn;
}
