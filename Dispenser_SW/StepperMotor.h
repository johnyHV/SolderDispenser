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

#ifndef __STEPPER_MOTOR_h_
#define __STEPPER_MOTOR_h_

#include <Arduino.h>
#include "MCU_cfg.h"

extern int  MotorSteps;     ///< aktualna poloha motora
extern uint16_t MotorSleep;     ///< dlzka sleep-u

#define MOTOR_PUSH      'F'     ///< priznak pre posun vpred
#define MOTOR_PULL      'B'     ///< priznak pre posun vzad
#define Motor460Steps   4095    ///< pocet krokov

#define MOTOR_MIN       1100    ///< maximalna rychlost spinania
#define MOTOR_MAX       10000   ///< minimalna rychlost spinania

void MotorInit();               ///< inicializacia motora
void MotorSetSleep(uint16_t);   ///< nastavenie dlzky sleepu medzi dalsim zopnutim cievok
void MotorStepper(uint8_t);     ///< dalsi krok 
void MotorOff();                ///< vypnutie motora
void SetDirection(uint8_t);     ///< nastavenie smeru motora

#endif
