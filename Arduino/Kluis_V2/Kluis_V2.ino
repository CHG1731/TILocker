/**@file Kluis_V2.ino*/
//Made by Felix Jochems
//Questions about the code? Mail felixjochems@gmail.com
//Version 1.1.14
/*
 * @mainpage Documentation
 * @section Felix Jochems
*/

//Libs used
#include <SPI.h>
#include <EEPROM.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

//Defining vault pins, so that they are easily switchable
#define KLUIS1 37 //Kluis 105
#define KLUIS2 33 //Kluis 106
#define KLUIS3 35 //Kluis 107
#define KLUIS4 31 //Kluis 108
#define KLUIS5 44 //Kluis 109
#define KLUIS6 40 //Kluis 110
#define KLUIS7 42 //Kluis 111
#define KLUIS8 38 //Kluis 112
#define KLUIS9 45 //Kluis 113
#define KLUIS10 41 //Kluis 114
#define KLUIS11 43 //Kluis 115
#define KLUIS12 39 //Kluis 116
#define KLUIS13 36 //Kluis 117
#define KLUIS14 32 //Kluis 118
#define KLUIS15 34 //Kluis 119
#define KLUIS16 30 //Kluis 120

//Define for custom offsets, this is mostly done to improve the readability of the code. Otherwise it would contain a lot of magic numbers
#define CHAROFFSET 48 //The bytes gained from the keypad minus this number results in human readable numbers
#define TEXTINTERVAL 6000 //Interval for text while idle
#define VAULTMEMOFFSET 105 //offset between vault numbers and vault memory locations
#define NUMBEROFVAULTS 16

//Settings
#define RFIDTIMEOUT 15 //Timeout for RFID search. The number put in is the amount of cycles the programs needs to do before it engages with another RFID card


//MFRC522 pins + init
#define RST_PIN 2
#define SS_PIN 53
MFRC522 mfrc522(SS_PIN, RST_PIN);

//init Keypad
const byte ROWS = 4;
const byte COLS = 4;
char Keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {8, 9, 10, 11};
Keypad cKeypad = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS);

//init LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);

bool admin = false; //set ADMIN mode
int vaultsMappedToPins[] = { KLUIS1, KLUIS2, KLUIS3, KLUIS4, KLUIS5, KLUIS6, KLUIS7, KLUIS8, KLUIS9, KLUIS10, KLUIS11, KLUIS12, KLUIS13, KLUIS14, KLUIS15, KLUIS16 };

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
int timeout = 0;
bool newcard = true;
int text = 0;
unsigned long previousMillis = 0;

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
      for (int i = 2000; i< 2085; i+=5)
      {
        if(mfrc522.uid.uidByte[0] == EEPROM.read(i))
        {
          i++;
          if(mfrc522.uid.uidByte[1] == EEPROM.read(i))
          {
            i++;
            if(mfrc522.uid.uidByte[2] == EEPROM.read(i))
            {
              i++;
              if(mfrc522.uid.uidByte[3] == EEPROM.read(i))
              {
                i++;
                int passMem = EEPROM.read(i);
                openVault(i, passMem);
                break;
              }
              else //FASE 4 BREAK
              {
                i-=4;
              }
            }
            else //FASE 3 BREAK
            {
              i-=3;
            }
          }
          else //FASE 2 BREAK
          {
            i-=2;
          }
        }
        else //FASE 1 BREAK
        {
          i-=1;
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
