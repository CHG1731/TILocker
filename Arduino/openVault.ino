void openVault(int vaultMem, int passMem)
{
  int vault =  vaultMem - 2004;
  int remainder = vault / 5;
  vault = 104 + remainder;
  setLCDtext("Pincode for ");
  lcd.print(vault+1);
  int passwdstep, tmp;
  bool cancel = false;
  byte first, second, third;
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
      if (passwdstep == 2) {
        first = tmp;
        tmp = 0;
      }
      if (passwdstep == 4) {
        second = tmp;
        tmp = 0;
      }
      if (passwdstep == 6) {
        third = tmp;
        if (EEPROM.read(passMem) == first)
        {
          if (EEPROM.read(passMem + 1) == second)
          {
            if (EEPROM.read(passMem + 2) == third)
            {
              //Serial.println("FULL MATCH FOUND, ACCES GRANTED");
              //Serial.println(vaultsMappedToPins[remainder]);
              digitalWrite(vaultsMappedToPins[remainder], HIGH);
              setLCDtext("Acces Granted", 6500);
              digitalWrite(vaultsMappedToPins[remainder], LOW);
            } else {
              setLCDtext("Acces Denied", 2000);
            }
          } else {
            setLCDtext("Acces Denied", 2000);
          }
        } else {
          setLCDtext("Acces Denied", 2000);
        }
        delay(random(300)); //Good luck with side channel analysis
        cancel = true;
        return;
      }
    }
  }
}

