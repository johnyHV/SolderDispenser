/**
 * @file StepperMotor.cpp
 *
 * @brief Ovladanie krokoveho motora
 *
 * @author Miroslav Pivovarsky
 * Contact: miroslav.pivovarsky@gmail.com
 * 
 * @bug: no know bug
 *
 */

#include "StepperMotor.h"

int MotorSteps = 0;
uint16_t MotorSleep = 0;

/**
 *
 * @info Inicializacia motora
 * @param none
 * @return none 
 */
void MotorInit() {
  pinMode(MOTOR_M1, OUTPUT);
  pinMode(MOTOR_M2, OUTPUT);
  pinMode(MOTOR_M3, OUTPUT);
  pinMode(MOTOR_M4, OUTPUT);
}

/**
 *
 * @info Nastavenie rychlosti spinania cievok
 * @param uint16_t - rychlost v uS
 * @return none 
 */
void MotorSetSleep(uint16_t val) {
  MotorSleep = val;
}

/**
 *
 * @info Funkcia pre spinanie cievok krokoveho motora
 * @param uint8_t - smer motora
 * @return none 
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
 *
 * @info Vypnutie krokoveho motora
 * @param none
 * @return none 
 */
void MotorOff() {
  digitalWrite(MOTOR_M1, LOW);
  digitalWrite(MOTOR_M2, LOW);
  digitalWrite(MOTOR_M3, LOW);
  digitalWrite(MOTOR_M4, LOW);
}

/**
 *
 * @info Nastavenie smeru otacania motora
 * @param int - smer
 * @return none 
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
