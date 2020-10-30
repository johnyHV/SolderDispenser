/**
   @file Config.h

   @brief kniznica s logikou

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#ifndef __CONFIG_h_
#define __CONFIG_h_

#include <Arduino.h>
#include <EEPROM.h>
#include "MCU_cfg.h"
#include "StepperMotor.h"

#define Mode_debounceDelay 50               ///< Ochrana proti zaknitu
#define Mode_debounceDelayAutoPull  5000    ///< Kontrola, ci uzivatel nechce prepnut na auto pull efekt

extern uint8_t Mode_buttonState;            ///< status tlacidla
extern uint8_t Mode_lastButtonState;        ///< status tlacidla v poslednom kole
extern unsigned long Mode_lastDebounceTime; ///< debounce time pre mod
extern unsigned long Mode_lastDebounceTimeAutoPull; ///< debounce time pre pull request
extern uint8_t ConfigModeStatus;            ///< Aktualny mod
extern uint8_t AutoPullSafety;              ///< poistka pre zapnutie/vypnutie auto pull modu

void ConfigInit();                          ///< konfiguracia periferii
void ConfigSetMod(int);                     ///< nastavenie rychlosti spinania pre dany mod
void ConfigSetLed(int);                     ///< nastavenie LED-ky
bool ConfigCheckButtonPush();               ///< kontrola stlacenia tlacidla PUSH
bool ConfigCheckButtonPull();               ///< kontrola stlacenia tlacidla PULL
bool ConfigCheckButtonMod();                ///< kontrola stlacenia tlacidla mode, pre zmenu rychlosti alebo zapis do EEPROM
bool ConfigCheckButtonModAutoPullEffect();  ///< kontrola stlacenia sekvencie pre zapnutie/vypnute auto pull modu
uint16_t ConfigGetTime();                   ///< ziskanie casu medzi spinanim cievok z trimra

void ConfigEepromWrite(uint16_t, uint16_t); ///< zapis do EEPROM pamete
uint16_t ConfigEepromRead(uint16_t);        ///< vycitanie z EEPROM pamete

#endif
