/**@file LCD.ino*/
void printVaultAvailability()
{
  lcd.setCursor(0, 0);
  setLCDtext("Available vaults");
  bool vault[15];
  int full = 0;
  for (int i = 200; i < 216; i++)
  {
    bool temp = EEPROM.read(i);
    vault[i - 200] = temp;
  }
  for (int i = 0; i < 16; i++)
  {
    if (!vault[i])
    {
      full++;
    }
  }
  lcd.setCursor(0, 1);
  int counter = 0;
  if (full == NUMBEROFVAULTS)
  {
    lcd.print("None available");
  }
  else
  {
    for (int i = 0; i < 16; i++)
    {
      if (vault[i])
      {
        counter++;
        lcd.print(i + VAULTMEMOFFSET);
        lcd.print(" ");
      }
      if (counter == 4)
      {
        counter = 0;
        delay(1500);
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(0, 1);
      }
    }
  }
}

void setLCDHome(int text)
{
  if (text == 1)
  {
    setLCDtext("Press A to", "register");
  }
  if (text == 2)
  {
    setLCDtext("Press B to see", "available vaults");
  }
  if (text == 3)
  {
    setLCDtext("Found a bug?Mail", "0911838@hr.nl");
  }
}

void setLCDpassword(int count)
{
  lcd.setCursor(0, 1);
  String passwd = "";
  for (int i = 0; i < count; i++)
  {
    passwd += '*';
  }
  lcd.print(passwd);
}
//Overloaded constructors
void setLCDtext(String A, String B, int delaytime)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(A);
  lcd.setCursor(0, 1);
  lcd.print(B);
  if (delaytime > 0)
  {
    delay(delaytime);
  }
}

void setLCDtext(String A, String B)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(A);
  lcd.setCursor(0, 1);
  lcd.print(B);
}

void setLCDtext(String A, int delaytime)
{
  String test = "";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(A);
  if (delaytime > 0)
  {
    delay(delaytime);
  }
}

void setLCDtext(String A)
{
  String test = "";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(A);
}

