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

extern int  MotorSteps;           ///< aktualna poloha motora
extern uint16_t MotorSleep;       ///< dlzka sleep-u
extern uint8_t MotorAutoPull;     ///< Informacia o tlacidlach pre auto pull efekt

#define MOTOR_PUSH      'F'       ///< priznak pre posun vpred
#define MOTOR_PULL      'B'       ///< priznak pre posun vzad
#define MOTOR_STOP      'S'       ///< priznak pre STOP motor
#define Motor460Steps   4095      ///< pocet krokov

#define MOTOR_MIN       1100      ///< maximalna rychlost spinania
#define MOTOR_MAX       10000     ///< minimalna rychlost spinania

void MotorInit();                 ///< inicializacia motora
void MotorSetSleep(uint16_t);     ///< nastavenie dlzky sleepu medzi dalsim zopnutim cievok
uint16_t MotorGetSleep();         ///< Ziskam aktualnu dlzku casu medzi krokmi
void MotorStepper(uint8_t);       ///< dalsi krok 
void MotorOff();                  ///< vypnutie motora
void SetDirection(uint8_t);       ///< nastavenie smeru motora
void MotorAutoPullEffect();       ///< Automaticky pull efekt o X krokov po pusteni PUSH tlacidla

#endif
