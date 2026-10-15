/*
 * Système d'Identification et de Suivi des marchandises par RFID
 * ----------------------------------------------------------------
 * Lecture d'un badge RFID (RC522, 13,56 MHz) -> recherche du cargo associé
 * -> affichage sur LCD I2C 16x2.
 *
 * Carte     : Arduino UNO
 * Librairies: MFRC522, LiquidCrystal_I2C
 */
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN 9    
#define SS_PIN 10    

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the I2C address (0x27) based on your LCD module.

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  lcd.init();       // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RFID Scanner");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return; // Wait for a new card
  }

  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reading UID...");
  delay(1000);

  String compileTime = String(__DATE__) + " " + String(__TIME__);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("UID: ");
  lcd.setCursor(0, 1);
  lcd.print(uid);
  delay(2000);

  lcd.clear();
  if (uid == "427eee3c") {
    lcd.setCursor(0, 0);
    lcd.print("Cargo: 1234");
    lcd.setCursor(0, 1);
    lcd.print("Algeria | Elec");
  } 
  else if (uid == "8bb0ae3") {
    lcd.setCursor(0, 0);
    lcd.print("Cargo: 5678");
    lcd.setCursor(0, 1);
    lcd.print("France | Furn");
  } 
  else if (uid == "e3a0d5d") {
    lcd.setCursor(0, 0);
    lcd.print("Cargo: 9101");
    lcd.setCursor(0, 1);
    lcd.print("USA | Apparel");
  } 
  else if (uid == "73166410") {
    lcd.setCursor(0, 0);
    lcd.print("Cargo: 1121");
    lcd.setCursor(0, 1);
    lcd.print("Canada | Food");
  } 
  else {
    lcd.setCursor(0, 0);
    lcd.print("Unknown UID");
    lcd.setCursor(0, 1);
    lcd.print("No data");
  }

  delay(3000); // Pause to allow reading on the LCD
  rfid.PICC_HaltA(); // Halt communication with the tag
}
