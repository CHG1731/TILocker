/**@file AdminMode.ino*/
void startAdminMode()
{
  bool cancel = false;
  setLCDtext("ADMIN MODE PRESS", "A FOR MORE INFO");
  while (!cancel)
  {
    char customKey = cKeypad.getKey();
    if (customKey)
    {
      if (customKey == 'A')
      {
        setLCDtext("COMMANDS: 1 FOR", "VAULT RESET", 1500);
        setLCDtext("COMMANDS: 2 FOR", "VAULT UNLOCK", 1500);
        setLCDtext("COMMANDS: 3 FOR", "MEMORY WIPE", 1500);
        setLCDtext("COMMANDS: 4 FOR", "MEMORY DUMP", 1500);
        setLCDtext("COMMANDS: * TO", "UNLOCK ALL VAULT", 1500);
        setLCDtext("COMMANDS: # TO", "LEAVE ADMIN MODE", 1500);
        setLCDtext("ADMIN MODE PRESS", "A FOR MORE INFO");
      }
      if (customKey == '1')
      {
        setLCDtext("SELECT VAULT");
        int vaultnr = 1;
        int vaultnr_step = 0;
        while (vaultnr_step < 3)
        {
          char customKey = cKeypad.getKey();
          if (customKey)
          {
            if (isNumeric(customKey))
            {
              vaultnr += (pow(10, (2 - vaultnr_step)) * (customKey - CHAROFFSET)); //pow(10,(2-vaultnr_step) = start with 100 then 10  then 1 || customKey - 48 is for char to int conversion
              lcd.setCursor(0, 1);
              lcd.print(vaultnr);
              vaultnr_step++;
              lcd.setCursor(vaultnr_step, 1);
              lcd.print("    ");
              if (vaultnr_step == 3 && vaultnr >= 105 && vaultnr <= 120)
              {
                setLCDtext("VAULT RESET", 1500);
                eeprom_admin_reset_vault(vaultnr);
                break;
              }
              else if (vaultnr_step == 3)
              {
                setLCDtext("INVALID VAULT", 1500);
                break;
              }
            }
            if (customKey == '#')
            {
              return;
            }
          }
        }
        setLCDtext("ADMIN MODE PRESS", "A FOR MORE INFO");
      }
      if (customKey == '2')
      {
        setLCDtext("SELECT VAULT");
        int vaultnr = 1;
        int vaultnr_step = 0;
        while (vaultnr_step < 3)
        {
          char customKey = cKeypad.getKey();
          if (customKey)
          {
            if (isNumeric(customKey))
            {
              vaultnr += (pow(10, (2 - vaultnr_step)) * (customKey - CHAROFFSET)); //pow(10,(2-vaultnr_step) = start with 100 then 10  then 1 || customKey - 48 is for char to int conversion
              lcd.setCursor(0, 1);
              lcd.print(vaultnr);
              vaultnr_step++;
              lcd.setCursor(vaultnr_step, 1);
              lcd.print("    ");
              if (vaultnr_step == 3 && vaultnr >= 105 && vaultnr <= 120)
              {
                setLCDtext("OPENING VAULT");
                lcd.print(vaultnr);
                digitalWrite(vaultsMappedToPins[vaultnr-105], HIGH);
                delay(5000);
                digitalWrite(vaultsMappedToPins[vaultnr-105], LOW);
              }
              else if (vaultnr_step == 3)
              {
                setLCDtext("INVALID VAULT", 1500);
                break;
              }
            }
            if (customKey == '#')
            {
              return;
            }
          }
        }
        setLCDtext("ADMIN MODE PRESS", "A FOR MORE INFO");
      }

      if (customKey == '3')
      {
        setLCDtext("WIPING MEMORY", "ARE YOU SURE?", 2500);
        setLCDtext("* to confirm", "# to cancel");
        while (!cancel)
        {
          char customKey = cKeypad.getKey();
          if (customKey)
          {
            if (customKey == '*')
            {
              lcd.setCursor(0, 1);
              lcd.print("***");
              resetRegisteredVaults();
              lcd.print("***");
              resetPasswords();
              lcd.print("***");
              resetVaultAvailability();;
              lcd.print("***");
              setLCDtext("WIPE FINISHED", 3000);
              cancel = true;
            }
            if (customKey == '#')
            {
              cancel = true;
            }
          }
        }
      }

      if (customKey == '4')
      {
        eeprom_serial_dump_column();
        cancel = true;
      }

      if (customKey == '*')
      {
        setLCDtext("OPENING ALL", "PRESS # TO QUIT");
        for (int i = 0; i < NUMBEROFVAULTS; i++)
        {
          digitalWrite(vaultsMappedToPins[i], HIGH);
          delay(50);
        }
      }
      if (customKey == '#')
      {
        cancel = true;
        for (int i = 0; i < NUMBEROFVAULTS; i++)
        {
          digitalWrite(vaultsMappedToPins[i], LOW);
        }
        return;
      }
    }
  }
}

