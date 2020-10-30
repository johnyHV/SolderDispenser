#include <Arduino.h>
#include <EEPROM.h>

#include "StepperMotor.h"
#include "Config.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Start MCU!");
  Serial.print("Software version: ");
  Serial.println(SOFTWARE_VERSION);

  /* inicializacia motora */
  MotorInit();

  /* inicializacia periferii  */
  ConfigInit();
  ConfigCheckButtonMod();
  delay(Mode_debounceDelay * 2);
  ConfigCheckButtonMod();

  /* nastavenie modu 1 */
  ConfigSetMod(1);

  /* nastavenie casu oneskorenia zopnutia dalsiej cievky */
  MotorSetSleep(ConfigEepromRead(E_MOD1));

}

void loop() {

  /* kontrola zapnutia/vypnutia auto pull efektu */
  if (ConfigCheckButtonModAutoPullEffect() == true) {
    MotorAutoPullEnDis(!MotorAutoPullStatus());

  } else {

    /* kontrola tlacidla pre zmenu modu */
    if (ConfigCheckButtonMod() == true) {
      ConfigModeStatus++;

      if (ConfigModeStatus > 5)
        ConfigModeStatus = 1;

      ConfigSetMod(ConfigModeStatus);
    }
  }

  /* kontrola tlacidiel pre ovladanie motora */
  if (ConfigCheckButtonPush() == false) {
    MotorStepper(MOTOR_PUSH);
    MotorAutoPull = MOTOR_PUSH;
  } else if (ConfigCheckButtonPull() == false) {
    MotorStepper(MOTOR_PULL);
    MotorAutoPull = MOTOR_PULL;
  } else {
    MotorOff();

    /* auto pull efekt, cize po pusteni PUSH tlacidla sa motor sam otoci spet o X krokov, aby netlacil na pastu */
    if (MotorAutoPull == MOTOR_PUSH) {
      Serial.print("Auto pull efekt: ");
      MotorAutoPullEffect();
    }
  }

  /* specialny mod pre citanie rychlosti z trimra */
  if (ConfigModeStatus == 5) {
    MotorSetSleep(ConfigGetTime());
  }
}
