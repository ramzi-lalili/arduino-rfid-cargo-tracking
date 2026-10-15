# Système d'Identification et de Suivi des marchandises par RFID

Prototype de suivi de cargaisons basé sur la technologie **RFID (13,56 MHz)** :
un lecteur **RC522** relié à un **Arduino UNO** lit l'identifiant unique (UID) d'un
badge collé sur un colis, retrouve les informations du cargo associé (numéro,
pays d'origine, type de marchandise) et les affiche sur un écran **LCD I2C 16x2**.

Projet réalisé dans le cadre du module *Électronique des systèmes embarqués*
(Département d'Électronique, Faculté de Génie Électrique, USTHB).

## Fonctionnalités implémentées

* Détection d'un nouveau badge RFID et lecture de son UID (SPI)
* Affichage de l'UID sur le LCD
* Association UID -> cargo (numéro, pays, type de marchandise)
* Message « Unknown UID » pour les badges non enregistrés

## Évolutions prévues (présentées dans la soutenance)

Ces éléments sont décrits dans [la présentation](docs/presentation_rfid_cargo_tracking.pptx)
mais ne sont pas encore dans le code actuel :

* Contrôle de la porte du cargo par servomoteur (vérification d'autorisation)
* Capteurs de température et d'humidité pour les conditions de stockage
* LED / buzzer pour les alertes
* Historique des déplacements (position, date, heure) et détection d'anomalies

## Matériel

|Composant|Détail|
|-|-|
|Microcontrôleur|Arduino UNO|
|Lecteur RFID|Module RC522 (13,56 MHz, SPI)|
|Badges|Cartes / tags MIFARE|
|Écran|LCD 16x2 avec module I2C (adresse `0x27`)|

Liste complète : [`hardware/bill\_of\_materials.md`](hardware/bill_of_materials.md)

## Branchements

|RC522|Arduino UNO|
|-|-|
|SDA (SS)|D10|
|SCK|D13|
|MOSI|D11|
|MISO|D12|
|RST|D9|
|3.3V|3.3V|
|GND|GND|

|LCD I2C|Arduino UNO|
|-|-|
|SDA|A4|
|SCL|A5|
|VCC|5V|
|GND|GND|

> Le RC522 s'alimente en \*\*3,3 V\*\*. Le brancher sur 5 V peut l'endommager.

!\[Schéma de câblage](docs/images/wiring\_arduino\_rc522.png)

## Installation

1. Installer **Arduino IDE**.
2. Installer les librairies (Gestionnaire de bibliothèques) :

   * **MFRC522** (Miguel Balboa)
   * **LiquidCrystal I2C**
3. Ouvrir `firmware/rfid\_cargo\_tracking/rfid\_cargo\_tracking.ino`.
4. Choisir la carte **Arduino UNO**, puis téléverser.
5. Passer un badge devant le lecteur.

## Ajouter un nouveau cargo

1. Passer le nouveau badge devant le lecteur : l'UID s'affiche sur le LCD.
2. Dans le `.ino`, ajouter un bloc `else if (uid == "...")` avec le numéro, le pays et le type de marchandise (16 caractères maximum par ligne).

## Cargos enregistrés (exemple)

|UID lu|Cargo|Origine|Type|
|-|-|-|-|
|`427eee3c`|1234|Algérie|Électronique|
|`8bb0ae3`|5678|France|Mobilier|
|`e3a0d5d`|9101|USA|Vêtements|
|`73166410`|1121|Canada|Alimentaire|

## Limitations connues

* **Format de l'UID :** les octets sont convertis en hexadécimal sans zéro initial
(`0x03` devient `3`), donc deux UID différents peuvent produire la même chaîne.
Pour un usage fiable, formater chaque octet sur deux chiffres, puis mettre à jour
les UID de la table.
* **UID codés en dur :** ajouter un cargo oblige à recompiler le programme. Une
évolution possible est une base de données ou une carte SD.
* **UID non sécurisé :** l'UID d'un badge MIFARE peut être copié. Il suffit pour un
prototype, pas pour un contrôle d'accès réel.
* Le programme utilise des `delay()` (6 s par lecture) et ne lit pas d'autre
badge pendant ce temps.

## Structure du dépôt

```
firmware/rfid\_cargo\_tracking/   Code Arduino
docs/                           Présentation et schéma de câblage
hardware/                       Liste du matériel
```

## Auteur

lalili mohamed ramzi – https://www.linkedin.com/in/ramzi-lalili-2948a8310/ – ramzilalili@gmail.com

## Licence

MIT, voir [`LICENSE`](LICENSE).

