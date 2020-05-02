/**
 * @file Config.cpp
 *
 * @brief kniznica s logikou
 *
 * @author Miroslav Pivovarsky
 * Contact: miroslav.pivovarsky@gmail.com
 * 
 * @bug: no know bug
 *
 */

#include "Config.h"

uint8_t Mode_buttonState = LOW;
uint8_t Mode_lastButtonState = LOW;
unsigned long Mode_lastDebounceTime = 0;
uint8_t ConfigModeStatus = 1;

/**
 *
 * @info Inicializacia periferii
 * @param none
 * @return none 
 */
void ConfigInit() {
  pinMode(LED_1,OUTPUT);
  pinMode(LED_2,OUTPUT);
  pinMode(LED_3,OUTPUT);
  pinMode(LED_4,OUTPUT);
  pinMode(LED_STATUS,OUTPUT);

  pinMode(BUTTON_PUSH, INPUT);
  pinMode(BUTTON_PULL, INPUT);
  pinMode(BUTTON_MOD, INPUT);

  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
  digitalWrite(LED_STATUS, LOW);

  Mode_lastButtonState = digitalRead(BUTTON_MOD);
}

/**
 *
 * @info nastavenie rychlosti spinania pre dany mod
 * @param int - mod
 * @return none 
 */
void ConfigSetMod(int Mod) {
  switch(Mod) {
    case 1:
      ConfigSetLed(1);
      MotorSetSleep(ConfigEepromRead(E_MOD1));
      break;
    case 2:
      ConfigSetLed(2);
      MotorSetSleep(ConfigEepromRead(E_MOD2));
      break;
    case 3:
      ConfigSetLed(3);
      MotorSetSleep(ConfigEepromRead(E_MOD3));
      break;
    case 4:
      ConfigSetLed(4);
      MotorSetSleep(ConfigEepromRead(E_MOD4));
      break;
    case 5:
      ConfigSetLed(5);
      break;
  }
}

/**
 *
 * @info zapnutie konkretnej LED-ky pre dany mod
 * @param int - led
 * @return none 
 */
void ConfigSetLed(int led) {
  switch (led) {
    case 1:
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, LOW);
      break;
    case 2:
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, LOW);
      break;
    case 3:
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, HIGH);
      digitalWrite(LED_4, LOW);
      break;
    case 4:
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, HIGH);
      break;
    case 5:
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, HIGH);
      digitalWrite(LED_4, HIGH);
      break;
  }
}

/**
 *
 * @info Kontrola stlacenia PUSH tlacidla
 * @param none
 * @return bool - status tlacidla 
 */
bool ConfigCheckButtonPush() {
  return digitalRead(BUTTON_PUSH);
}

/**
 *
 * @info Kontrola stlacenia PULL tlacidla
 * @param none
 * @return bool - status tlacidla 
 */
bool ConfigCheckButtonPull() {
   return digitalRead(BUTTON_PULL);
}

/**
 *
 * @info Kontrola stlacenia MODE tlacidla
 * @param none
 * @return bool - status tlacidla 
 */
bool ConfigCheckButtonMod() {
  int Mode_reading = digitalRead(BUTTON_MOD);
  
  if (Mode_reading != Mode_lastButtonState) {
    Mode_lastDebounceTime = millis();
  }

  /* kontrola, ci tlacidlo bolo dostatocne dlho stlacene */
  if ((millis() - Mode_lastDebounceTime) > Mode_debounceDelay) {

    if (Mode_reading != Mode_buttonState) {
      Mode_buttonState = Mode_reading;

      /* kontrola, ci je stlacene aj PULL tlacidlo, a ci ide o zapis hodnoty do EEPROM pamete pre dany mod */
      if ((ConfigCheckButtonPull() == false) && (Mode_buttonState == HIGH)) {
        digitalWrite(LED_STATUS, HIGH);
        
        int value = ConfigGetTime();
        Serial.print("Analog: ");
        Serial.println(value); 
        switch(ConfigModeStatus) {
          case 1:
            ConfigEepromWrite(E_MOD1, value);
            break;
          case 2:
            ConfigEepromWrite(E_MOD2, value);
            break;
          case 3:
            ConfigEepromWrite(E_MOD3, value);
            break;
          case 4:
            ConfigEepromWrite(E_MOD4, value);
            break;
        }

        ConfigSetMod(ConfigModeStatus);
        Mode_lastButtonState = Mode_reading;
        delay(500);
        digitalWrite(LED_STATUS, LOW);
        return false;
      }
      
      if (Mode_buttonState == HIGH) {
        return true;  
      }
    }
  }
  
  Mode_lastButtonState = Mode_reading;
  return false;
}

/**
 *
 * @info Funkcia ktora prepocita analogovu hodnotu na cas rychlosti spinania cievok
 * @param none
 * @return int - cas
 */
uint16_t ConfigGetTime() {
  uint16_t ret = analogRead(SPEED)*10;

  if (ret < MOTOR_MIN)
    ret = MOTOR_MIN;

  return ret;
}

/**
 *
 * @info Funkcia pre zapis hodnoty 16bit do EEPROM pamete
 * @param uint16_t - Adresa pamete
 * @param uint16_t - hodnota
 * @return none
 */
void ConfigEepromWrite(uint16_t Add, uint16_t val) {
  uint8_t UP = val >> 8;
  uint8_t DOWN = val & 0xFF;

  Serial.print("EEPROM Write: ");
  Serial.print(Add);
  Serial.print(" - ");
  Serial.print(val);
  Serial.print(" -> ");
  Serial.print(UP);
  Serial.print("|");
  Serial.println(DOWN);
  
  EEPROM.write(Add, UP);
  EEPROM.write(Add + 1, DOWN);
}

/**
 *
 * @info Vycitanie 16bit hodnoty z EEPROM pamete
 * @param uint16_t - Adresa pamete
 * @return uint16_t - hodnota na adrese
 */
uint16_t ConfigEepromRead(uint16_t Add) {
  int retUp = EEPROM.read(Add);
  int retDown = EEPROM.read(Add+1);

  int ret = (retUp << 8) | retDown;
  Serial.print("EEPROM Read: ");
  Serial.print(Add);
  Serial.print(" - ");
  Serial.print(ret);
  Serial.print(" -> ");
  Serial.print(retUp);
  Serial.print("|");
  Serial.println(retDown);
  
  return ret;
}
