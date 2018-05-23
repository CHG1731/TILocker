/**@file Kluis_V2.ino*/
/*! \mainpage Documentation
 *
 * \section intro_sec Introduction
 *
 * This is the documentation for the lockers in the hallway at TI
 *
 * \section Brief file descriptions
 *
 * \subsection step1 Kluis_v2
 * This is the main file with all the settings
 * \subsection step2 AdminMode
 * This file contains the loop voor the administrator mode
 * \subsection step3 EEPROM
 * This file contains all the code for the EEPROM reset. It's a handy guide for the index of all locations
 * \subsection step4 LCD
 * This file contains the vault availability function, the standby scrolling text and an overloaded function for displaying text. See the LCD file for more information.
 * \subsection step5 RegisterNewVault
 * This file is used while registering a new vault. This file gets called in the main loop.
 * \subsection step6 Utilities
 * Small file with some utilities used in the rest of the code
 * \subsection step7 OpenVault
 * Just like RegisterNewVault this gets called in the main loop. This file handles the opening of the vaults given the memory location of the password and RFID card
 */
//Made by Felix Jochems
//Questions about the code? Mail felixjochems@gmail.com
//Version 1.1.14

//Libs used
#include <SPI.h> 
#include <EEPROM.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

//Defining vault pins, so that they are easily switchable
#define KLUIS1 37 ///< Kluis 105 
#define KLUIS2 33 ///< Kluis 106
#define KLUIS3 35 ///< Kluis 107
#define KLUIS4 31 ///< Kluis 108
#define KLUIS5 44 ///< Kluis 109
#define KLUIS6 40 ///< Kluis 110
#define KLUIS7 42 ///< Kluis 111
#define KLUIS8 38 ///< Kluis 112
#define KLUIS9 45 ///< Kluis 113
#define KLUIS10 41 ///< Kluis 114
#define KLUIS11 43 ///< Kluis 115
#define KLUIS12 39 ///< Kluis 116
#define KLUIS13 36 ///< Kluis 117
#define KLUIS14 32 ///< Kluis 118
#define KLUIS15 34 ///< Kluis 119
#define KLUIS16 30 ///< Kluis 120

//Define for custom offsets, this is mostly done to improve the readability of the code. Otherwise it would contain a lot of magic numbers
#define CHAROFFSET 48  ///< The bytes gained from the keypad minus this number results in human readable numbers 
#define TEXTINTERVAL 6000  ///< Interval (in milliseconds) for text while idle
#define VAULTMEMOFFSET 105  ///< offset between vault numbers and vault memory locations
#define NUMBEROFVAULTS 16

//Settings
#define RFIDTIMEOUT 15 ///< Timeout for RFID search. The number put in is the amount of cycles the programs needs to do before it engages with another RFID card
#define DEBUG false ///< Setting to show debug information via serial

//MFRC522 pins + init
#define RST_PIN 2 ///< Reset pin for the MFRC522
#define SS_PIN 53 ///< Slave select pin for the MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN); ///< Init RFID Scanner

//init Keypad
char Keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
}; ///< Keypad mapped to characters
byte rowPins[4] = {4, 5, 6, 7}; ///< Row pins used for the keypad
byte colPins[4] = {8, 9, 10, 11}; ///< Column pins used for the keypad
Keypad cKeypad = Keypad( makeKeymap(Keys), rowPins, colPins, 4, 4); ///< Init the keypad

//init LCD
LiquidCrystal_I2C lcd(0x27, 20, 4); ///< Init LCD

bool admin = false; ///< Admin mode, default is false
int vaultsMappedToPins[] = { KLUIS1, KLUIS2, KLUIS3, KLUIS4, KLUIS5, KLUIS6, KLUIS7, KLUIS8, KLUIS9, KLUIS10, KLUIS11, KLUIS12, KLUIS13, KLUIS14, KLUIS15, KLUIS16 }; ///< Vaults mapped to pins, so that changing a vault to a different pin causes little change

void setup() {

  //Serial
  Serial.begin(115200);

  //Init Vault pins for output
  pinMode(KLUIS1, OUTPUT);
  pinMode(KLUIS2, OUTPUT);
  pinMode(KLUIS3, OUTPUT);
  pinMode(KLUIS4, OUTPUT);
  pinMode(KLUIS5, OUTPUT);
  pinMode(KLUIS6, OUTPUT);
  pinMode(KLUIS7, OUTPUT);
  pinMode(KLUIS8, OUTPUT);
  pinMode(KLUIS9, OUTPUT);
  pinMode(KLUIS10, OUTPUT);
  pinMode(KLUIS11, OUTPUT);
  pinMode(KLUIS12, OUTPUT);
  pinMode(KLUIS13, OUTPUT);
  pinMode(KLUIS14, OUTPUT);
  pinMode(KLUIS15, OUTPUT);
  pinMode(KLUIS16, OUTPUT);

  //MFRC522 INIT
  SPI.begin();
  mfrc522.PCD_Init();

  //Seed the PRNG
  randomSeed(analogRead(A8));

  //Setup for admin mode
  pinMode(13, INPUT_PULLUP);
  if (digitalRead(13) == LOW)
  {
    admin = true;
  }

  lcd.init();
  lcd.backlight();
}

//Global variables
int timeout = 0; ///< Variable for timeout cycles, see RFIDTIMEOUT
bool newcard = true; ///< Boolean so that the scanner doesnt scan every card while out of main loop
int text = 0; ///< Variable to show the standby text
unsigned long previousMillis = 0; ///< Variable to keep track of the time, see TEXTINTERVAL

void loop()
{
  if (admin)
  {
    bool cancel = false;
    setLCDtext("ENTER ADMIN KEY");
    int adminkey = 1;
    int keystep = 0;
    while (!cancel)
    {
      char customKey = cKeypad.getKey();
      if (isNumeric(customKey))
      {
        adminkey += (pow(10, (3 - keystep)) * (customKey - CHAROFFSET));
        keystep++;
        if (keystep == 4)
        {
          if (EEPROM.read(adminkey) == 128)
          {
            startAdminMode();
            admin = false;
            cancel = true;
            return;
          }
          else
          {
            setLCDtext("ERROR, ABORTING", "ADMIN MODE", 3000);
            admin = false;
            return;
          }
        }
      }
      if (customKey == '#')
      {
        setLCDtext("ABORTING", "ADMIN MODE", 3000);
        admin = false;
        return;
      }
    }
  }

  char customKey = cKeypad.getKey();
  if (timeout == RFIDTIMEOUT) {
    newcard = true;  //reset timeout for RFID card
  }
  timeout++;

  if (customKey == 'A')
  {
    registerNewVault();
  }

  if (customKey == 'B')
  {
    printVaultAvailability();
  }

  if (mfrc522.PICC_IsNewCardPresent())
  {
    timeout = 0;
    if (mfrc522.PICC_ReadCardSerial() && newcard)
    {
      newcard = false;
      for (int i = 2000; i<=2075; i+=5)
      {
        if(DEBUG) { Serial.print("BYTE 0(RFID): ");Serial.print(mfrc522.uid.uidByte[0],HEX);Serial.print(" BYTE 0(EEPROM): ");Serial.print(EEPROM.read(i),HEX);Serial.print("    I:");Serial.print(i);Serial.println(); }
        if(mfrc522.uid.uidByte[0] == EEPROM.read(i))
        {
          i++;
          if(DEBUG) { Serial.print("BYTE 1(RFID): ");Serial.print(mfrc522.uid.uidByte[1],HEX);Serial.print(" BYTE 1(EEPROM): ");Serial.print(EEPROM.read(i),HEX);Serial.print("    I:");Serial.print(i);Serial.println(); }
          if(mfrc522.uid.uidByte[1] == EEPROM.read(i))
          {
            i++;
            if(DEBUG) { Serial.print("BYTE 2(RFID): ");Serial.print(mfrc522.uid.uidByte[2],HEX);Serial.print(" BYTE 2(EEPROM): ");Serial.print(EEPROM.read(i),HEX);Serial.print("    I:");Serial.print(i);Serial.println(); }
            if(mfrc522.uid.uidByte[2] == EEPROM.read(i))
            {
              i++;
              if(DEBUG) { Serial.print("BYTE 3(RFID): ");Serial.print(mfrc522.uid.uidByte[3],HEX);Serial.print(" BYTE 3(EEPROM): ");Serial.print(EEPROM.read(i),HEX);Serial.print("    I:");Serial.print(i);Serial.println(); }
              if(mfrc522.uid.uidByte[3] == EEPROM.read(i))
              {
                i++;
                int passMem = EEPROM.read(i);
                openVault(i, passMem);
                break;
              }
              else //FASE 4 BREAK
              {
                i-=3;
              }
            }
            else //FASE 3 BREAK
            {
              i-=2;
            }
          }
          else //FASE 2 BREAK
          {
            i-=1;
          }
        }
        else //FASE 1 BREAK
        {
          //DO NOTHING
        }
      }
      delay(1000);
    }
  } 
      /*
      for (int i = 2000; i < 2085; i += 5) //Match UID of card with memory locations for card UID's
      {
        if (mfrc522.uid.uidByte[0] != EEPROM.read(i)) { }
        else {
          i++;
          if (mfrc522.uid.uidByte[1] != EEPROM.read(i)) { }
          else {
            i++;
            if (mfrc522.uid.uidByte[2] != EEPROM.read(i)) {  }
            else {
              i++;
              if (mfrc522.uid.uidByte[3] != EEPROM.read(i)) {  }
              else {
                i++;
                int passMem = EEPROM.read(i);
                openVault(i, passMem);
                break;
              }
            }
          }
        }
      }
      delay(1000);
    }
  }
  */

  unsigned long startTime = millis();
  if (startTime - previousMillis > TEXTINTERVAL)
  {
    previousMillis = startTime;
    text++;
    if (text > 3)
    {
      text = 0;
    }
    setLCDHome(text);
  }
}
