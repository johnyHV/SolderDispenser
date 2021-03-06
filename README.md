# Solder paste dispenser

![Image description](FOTO/IMG_20200416_170805_621.jpg)

# Change Log

### Version 1.1 [HW v1.1, SW v1.1]
- pridana funkcia auto pull efektu. Toznamena, ze po pusteni PUSH tlacidla sa krokovy motor otoci o X krokov spat, vdaka comu prestane tlacit na spajkovaciu pastu. Efekt mozete zapnut pomocou definicie **M_A_PULL_E** v subore **MCU_cfg.h**.  Definiciou **M_A_PULL_ST** nastavujete pocet krokov o kolko sa krokov motor vrati spet. Tuto hodnotu je potrebne odladit pre kazdeho uzivatela, no myslim ze 100 krokov bude dost. Definiciou **M_A_PULL_SP** nastavite rychlost otacania krokoveho motora, pri otacani.
- pridany vypis SW verzie do konzoly
- aktualizovana doxygen dokumentacia

### Version 1.2 [HW v1.1, SW v1.2]
- pridana moznost zapnutia/vypnutia auto pull modu pomocou tlacidiel.  Defaultne je auto pull mod vypnuty, pomocou definicie **M_A_PULL_E**. Pre zapnutie je potrebne podrzat 5 sekund tlacidlo **MODE**. Po 5 sekundach zsvieti led **STATUS** na 1 sekundu. Vtedy je potrebne pustit tlacidlo **MODE**. Touto sekvenciou bol zapnuty auto pull mod. Ak ho chcete vypnut, znova je potrebne podrzat 5 sekund tlacidlo  **MODE**. Volba zapnutia/vypnutia auto pull modu sa neuklada do EEPROM pamete, cize po kazdom restarte je nastavena na hodnotu v definicii **M_A_PULL_E**.
- aktualizacia doxygen dokumentacie

### Version 1.3 [HW v1.2, SW v1.2]
- pridany kondenzator 1uF k napajaniu MCU

### Version 1.4 [HW v1.3, SW v1.2]
- pridany kondenzator 100nF k CH340 na 3,3V vystup.

# Bug

### Bug 0001
**Opis chyby:** 
chyba v HW zapojeni pre HW verzie 1.0, 1.1, 1.2. Chybajuci kondenzator 100nF pre CH340 na pine 4, proti zemi.

**Spravanie chyby:**
- OS moze mat problem pri detegcii zariadenia, v pripade pouzitia dlheho USB kabla. Pri dlzke kabla do 20cm bude zariadenie fungovat korektne.
- Moze vzniknut problem pri programovani MCU, kedy OS vypise hlasku nedetegovaneho USB zariadenia.
- Nahodne restarty MCU pocas pouzivania podavaca

**Riesenie:**
- potrebne prispajkovat kondenzator 100nF na pin 4 integrovaneho obvodu CH340 proti zemi. Tak ako je to zobrazene na fotografii
![Image description](FOTO/bug0001/DSCF6063.png)
