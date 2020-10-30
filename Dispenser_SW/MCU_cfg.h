/**
 * @file MCU_cfg.h
 *
 * @brief Konfiguracia procesora
 *
 * @author Miroslav Pivovarsky
 * Contact: miroslav.pivovarsky@gmail.com
 * 
 * @bug: no know bug
 *
 */

#ifndef __MCU_h_
#define __MCU_h_

#define SOFTWARE_VERSION "1.1"

#define MOTOR_M1    3         ///< Motor pin 1
#define MOTOR_M2    2         ///< Motor pin 2
#define MOTOR_M3    4         ///< Motor pin 3
#define MOTOR_M4    5         ///< Motor pin 4
  
#define LED_1       6         ///< LED mod 1
#define LED_2       7         ///< LED mod 2
#define LED_3       8         ///< LED mod 3
#define LED_4       9         ///< LED mod 4
#define LED_STATUS  13        ///< LED status

#define BUTTON_PUSH 15        ///< tlacidlo pre posun vpred
#define BUTTON_PULL 16        ///< tlacidlo pre posun vzad
#define BUTTON_MOD  17        ///< tlacidlo pre zmenu modu

#define SPEED       A0        ///< analogovy vstup

#define E_MOD1      1         ///< EEPROM adresa pre MOD 1
#define E_MOD2      3         ///< EEPROM adresa pre MOD 2
#define E_MOD3      5         ///< EEPROM adresa pre MOD 3
#define E_MOD4      7         ///< EEPROM adresa pre MOD 4

#define M_A_PULL_E  false      ///< Zapnutie/vypnute auto pull efektu. true - zapnuty,  false - vypnuty
#define M_A_PULL_ST 100       ///< Pocet krokov, ktore spravi motor pri auto pull efekte
#define M_A_PULL_SP 4000      ///< Rychlost motora, akou sa bude otacat pri auto pull efekte

#endif
