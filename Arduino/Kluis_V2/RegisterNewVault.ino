void registerNewVault()
{
  checkVaultAvailability();
}

void checkVaultAvailability()
{
  setLCDtext("Type vault Nr.");
  int vaultnr_step = 0;
  int vaultnr = 1;
  while (vaultnr_step < 3)
  {
    char customKey = cKeypad.getKey();
    if (customKey)
    {
      if (isNumeric(customKey))
      {
        vaultnr += (pow(10, (2 - vaultnr_step)) * (customKey - CHAROFFSET));
        lcd.setCursor(0, 1);
        lcd.print(vaultnr);
        vaultnr_step++;
        lcd.setCursor(vaultnr_step, 1);
        lcd.print("   "); //clear after the vaultnr
      }
      if (customKey == '#')
      {
        setLCDHome(2);
        return;
      }
    }
  }
  if (vaultnr >= 105 && vaultnr <= 120)
  {
    if (EEPROM.read(vaultnr + 95))
    {
      registerVault(vaultnr);
    }
    else
    {
      setLCDtext("This one", "is already taken", 2500);
    }
  }
  else
  {
    setLCDtext("Does not exist", 2500);
  }
}

void registerVault(int vaultnr)
{
  setLCDtext("Scan card to", "register");
  bool cancel = false;
  while (!cancel)
  {
    char customKey = cKeypad.getKey();
    if (customKey)
    {
      if (customKey == '#')
      {
        cancel = true;
        return;
      }
    }
    if (mfrc522.PICC_IsNewCardPresent())
    {
      if (mfrc522.PICC_ReadCardSerial())
      {
        for (int i = 2000; i < 2080; i += 5) //Match UID of card with memory locations for card UID's
        {
          if (mfrc522.uid.uidByte[0] != EEPROM.read(i)) {
            /*Serial.print("Byte in MFRC: "); Serial.print("STAGE 1: "); Serial.print(EEPROM.read(i),BIN); Serial.print(" BYTE RECEIVED: "); Serial.println(mfrc522.uid.uidByte[0],BIN); */
          }
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
                  setLCDtext("This card is", "not eglible", 2500);
                  cancel = true;
                  return;
                }
              }
            }
          }
        }
        registerPin(vaultnr);
        cancel = true;
      }
    }
  }
}

void registerPin(int vaultnr)
{
  setLCDtext("Enter 6digit pin");
  bool cancel = false;
  byte first, second, third;
  int tmp = 0;
  int passwdstep = 0;
  while (!cancel)
  {
    char customKey = cKeypad.getKey();
    if (customKey)
    {
      if (customKey == '#')
      {
        cancel = true;
        return;
      }
      if (isNumeric(customKey))
      {
        if (passwdstep % 2 == 0)
        {
          tmp += ((customKey - CHAROFFSET) * 10);
        }
        else
        {
          tmp += (customKey - CHAROFFSET);
        }
        passwdstep++;
        setLCDpassword(passwdstep);
        if (passwdstep == 2)
        {
          first = tmp;
          tmp = 0;
        }
        if (passwdstep == 4)
        {
          second = tmp;
          tmp = 0;
        }
        if (passwdstep == 6)
        {
          third = tmp;
          finaliseVaultRegistry(vaultnr, first, second, third);
          cancel = true;
          return;
        }
      }
    }
  }
}

void finaliseVaultRegistry(int vaultnr, byte first, byte second, byte third)
{
  int vaultMemLoc = vaultToMemLoc(vaultnr);
  int passMemLoc = EEPROM.read(vaultMemLoc + 4);
  for (int i = vaultMemLoc; i < vaultMemLoc + 4; i++)
  {
    EEPROM.write(i, mfrc522.uid.uidByte[i - vaultMemLoc]);
  }
  EEPROM.write(passMemLoc, first);
  EEPROM.write(passMemLoc + 1, second);
  EEPROM.write(passMemLoc + 2, third);
  EEPROM.write(vaultnr + 95, 0);
  setLCDtext("Scan card", "to open vault", 2000);
  return;
}

