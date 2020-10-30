# Solder paste dispenser

![Image description](FOTO/IMG_20200416_170805_621.jpg)

[Change Log]

Version 1.1
- pridana funkcia auto pull efektu. Toznamena, ze po pusteni PUSH tlacidla sa krokovy motor otoci o X krokov spat, vdaka comu prestane tlacit na spajkovaciu pastu. Efekt mozete zapnut pomocou definicie **M_A_PULL_E** v subore **MCU_cfg.h**.  Definiciou **M_A_PULL_ST** nastavujete pocet krokov o kolko sa krokov motor vrati spet. Tuto hodnotu je potrebne odladit pre kazdeho uzivatela, no myslim ze 100 krokov bude dost. Definiciou **M_A_PULL_SP** nastavite rychlost otacania krokoveho motora, pri otacani.
- pridany vypis SW verzie do konzoly
- aktualizovana doxygen dokumentacia
