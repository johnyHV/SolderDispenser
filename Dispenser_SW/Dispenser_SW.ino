#include <Arduino.h>
#include <EEPROM.h>

#include "StepperMotor.h"
#include "Config.h"

void setup() {
  Serial.begin(115200);
  Serial.println("StartMCU");

  /* inicializacia motora */
  MotorInit();

  /* inicializacia periferii  */
  ConfigInit();
  ConfigCheckButtonMod();
  delay(Mode_debounceDelay*2);
  ConfigCheckButtonMod();

  /* nastavenie modu 1 */
  ConfigSetMod(1);
  
  /* nastavenie casu oneskorenia zopnutia dalsiej cievky */
  MotorSetSleep(ConfigEepromRead(E_MOD1));

}

void loop() {
  /* kontrola tlacidla pre zmenu modu */
  if (ConfigCheckButtonMod() == true) {
    ConfigModeStatus++;
    
    if (ConfigModeStatus > 5)
      ConfigModeStatus = 1;
    
    ConfigSetMod(ConfigModeStatus);
  }

  /* kontrola tlacidiel pre ovladanie motora */
  if (ConfigCheckButtonPush() == false) {
    MotorStepper(MOTOR_PUSH);
  } else if (ConfigCheckButtonPull() == false) {
    MotorStepper(MOTOR_PULL);
  } else {
    MotorOff();
  }

  /* specialny mod pre citanie rychlosti z trimra */
  if (ConfigModeStatus == 5) {
    MotorSetSleep(ConfigGetTime());
  }
}
