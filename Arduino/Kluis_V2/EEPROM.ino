const int EEPROM_MIN_ADDR = 0;
const int EEPROM_MAX_ADDR = 4096;

void resetVaultAvailability() //True = open | False = closed
{
  EEPROM.write(200, 1); //Kluis 105
  EEPROM.write(201, 1); //Kluis 106
  EEPROM.write(202, 1); //Kluis 107
  EEPROM.write(203, 1); //Kluis 108
  EEPROM.write(204, 1); //Kluis 109
  EEPROM.write(205, 1); //Kluis 110
  EEPROM.write(206, 1); //Kluis 111
  EEPROM.write(207, 1); //Kluis 112
  EEPROM.write(208, 1); //Kluis 113
  EEPROM.write(209, 1); //Kluis 114
  EEPROM.write(210, 1); //Kluis 115
  EEPROM.write(211, 1); //Kluis 116
  EEPROM.write(212, 1); //Kluis 117
  EEPROM.write(213, 1); //Kluis 118
  EEPROM.write(214, 1); //Kluis 119
  EEPROM.write(215, 1); //Kluis 120
}

void resetPasswords()
{
  //Kluis 105
  EEPROM.write(10, 0xFF);
  EEPROM.write(11, 0xFF);
  EEPROM.write(12, 0xFF);

  //Kluis 106
  EEPROM.write(20, 0xFF);
  EEPROM.write(21, 0xFF);
  EEPROM.write(22, 0xFF);

  //Kluis 107
  EEPROM.write(30, 0xFF);
  EEPROM.write(31, 0xFF);
  EEPROM.write(32, 0xFF);

  //Kluis 108
  EEPROM.write(40, 0xFF);
  EEPROM.write(41, 0xFF);
  EEPROM.write(42, 0xFF);

  //Kluis 109
  EEPROM.write(50, 0xFF);
  EEPROM.write(51, 0xFF);
  EEPROM.write(52, 0xFF);

  //Kluis 110
  EEPROM.write(60, 0xFF);
  EEPROM.write(61, 0xFF);
  EEPROM.write(62, 0xFF);

  //Kluis 111
  EEPROM.write(70, 0xFF);
  EEPROM.write(71, 0xFF);
  EEPROM.write(72, 0xFF);


  //Kluis 112
  EEPROM.write(80, 0xFF);
  EEPROM.write(81, 0xFF);
  EEPROM.write(82, 0xFF);

  //Kluis 113
  EEPROM.write(90, 0xFF);
  EEPROM.write(91, 0xFF);
  EEPROM.write(92, 0xFF);

  //Kluis 114
  EEPROM.write(100, 0xFF);
  EEPROM.write(101, 0xFF);
  EEPROM.write(102, 0xFF);

  //Kluis 115
  EEPROM.write(110, 0xFF);
  EEPROM.write(111, 0xFF);
  EEPROM.write(112, 0xFF);

  //Kluis 116
  EEPROM.write(120, 0xFF);
  EEPROM.write(121, 0xFF);
  EEPROM.write(122, 0xFF);

  //Kluis 117
  EEPROM.write(130, 0xFF);
  EEPROM.write(131, 0xFF);
  EEPROM.write(142, 0xFF);

  //Kluis 118
  EEPROM.write(140, 0xFF);
  EEPROM.write(141, 0xFF);
  EEPROM.write(142, 0xFF);

  //Kluis 119
  EEPROM.write(150, 0xFF);
  EEPROM.write(151, 0xFF);
  EEPROM.write(152, 0xFF);


  //Kluis 120
  EEPROM.write(160, 0xFF);
  EEPROM.write(161, 0xFF);
  EEPROM.write(162, 0xFF);
}

void resetRegisteredVaults()
{
  //1 || KLUISJE 105
  EEPROM.write(2000, 0xFF);
  EEPROM.write(2001, 0xFF);
  EEPROM.write(2002, 0xFF);
  EEPROM.write(2003, 0xFF);
  EEPROM.write(2004, 10);

  //2 || KLUISJE 106
  EEPROM.write(2005, 0xFF);
  EEPROM.write(2006, 0xFF);
  EEPROM.write(2007, 0xFF);
  EEPROM.write(2008, 0xFF);
  EEPROM.write(2009, 20);

  //3 || KLUISJE 107
  EEPROM.write(2010, 0xFF);
  EEPROM.write(2011, 0xFF);
  EEPROM.write(2012, 0xFF);
  EEPROM.write(2013, 0xFF);
  EEPROM.write(2014, 30);

  //4 || KLUISJE 108
  EEPROM.write(2015, 0xFF);
  EEPROM.write(2016, 0xFF);
  EEPROM.write(2017, 0xFF);
  EEPROM.write(2018, 0xFF);
  EEPROM.write(2019, 40);

  //5 || KLUISJE 109
  EEPROM.write(2020, 0xFF);
  EEPROM.write(2021, 0xFF);
  EEPROM.write(2022, 0xFF);
  EEPROM.write(2023, 0xFF);
  EEPROM.write(2024, 50);

  //6 || KLUISJE 110
  EEPROM.write(2025, 0xFF);
  EEPROM.write(2026, 0xFF);
  EEPROM.write(2027, 0xFF);
  EEPROM.write(2028, 0xFF);
  EEPROM.write(2029, 60);

  //7 || KLUISJE 111
  EEPROM.write(2030, 0xFF);
  EEPROM.write(2031, 0xFF);
  EEPROM.write(2032, 0xFF);
  EEPROM.write(2033, 0xFF);
  EEPROM.write(2034, 70);

  //8 || KLUISJE 112
  EEPROM.write(2035, 0xFF);
  EEPROM.write(2036, 0xFF);
  EEPROM.write(2037, 0xFF);
  EEPROM.write(2038, 0xFF);
  EEPROM.write(2039, 80);

  //9 || KLUISJE 113
  EEPROM.write(2040, 0xFF);
  EEPROM.write(2041, 0xFF);
  EEPROM.write(2042, 0xFF);
  EEPROM.write(2043, 0xFF);
  EEPROM.write(2044, 90);

  //10 || KLUISJE 114
  EEPROM.write(2045, 0xFF);
  EEPROM.write(2046, 0xFF);
  EEPROM.write(2047, 0xFF);
  EEPROM.write(2048, 0xFF);
  EEPROM.write(2049, 100);

  //11 || KLUISJE 115
  EEPROM.write(2050, 0xFF);
  EEPROM.write(2051, 0xFF);
  EEPROM.write(2052, 0xFF);
  EEPROM.write(2053, 0xFF);
  EEPROM.write(2054, 110);

  //12 || KLUISJE 116
  EEPROM.write(2055, 0xFF);
  EEPROM.write(2056, 0xFF);
  EEPROM.write(2057, 0xFF);
  EEPROM.write(2058, 0xFF);
  EEPROM.write(2059, 120);

  //13 || KLUISJE 117
  EEPROM.write(2060, 0xFF);
  EEPROM.write(2061, 0xFF);
  EEPROM.write(2062, 0xFF);
  EEPROM.write(2063, 0xFF);
  EEPROM.write(2064, 130);

  //14 || KLUISJE 118
  EEPROM.write(2065, 0xFF);
  EEPROM.write(2066, 0xFF);
  EEPROM.write(2067, 0xFF);
  EEPROM.write(2068, 0xFF);
  EEPROM.write(2069, 140);

  //15 || KLUISJE 119
  EEPROM.write(2070, 0xFF);
  EEPROM.write(2071, 0xFF);
  EEPROM.write(2072, 0xFF);
  EEPROM.write(2073, 0xFF);
  EEPROM.write(2074, 150);

  //16 || KLUISJE 120
  EEPROM.write(2075, 0xFF);
  EEPROM.write(2076, 0xFF);
  EEPROM.write(2077, 0xFF);
  EEPROM.write(2078, 0xFF);
  EEPROM.write(2079, 160);
}

void eeprom_serial_dump_column() //Copied directly from the arduino website
{
  // counter
  int i;

  // byte read from eeprom
  byte b;

  // buffer used by sprintf
  char buf[10];
  setLCDtext("DUMPING MEMORY");
  lcd.setCursor(0, 1);
  for (i = EEPROM_MIN_ADDR; i <= EEPROM_MAX_ADDR; i++) {
    if (i % 256 == 0)
    {
      lcd.print("*");
    }
    b = EEPROM.read(i);
    sprintf(buf, "%03X: %02X", i, b);
    Serial.println(buf);
  }
}

void eeprom_admin_reset_vault(int vault)
{
  int vaultMem = vaultToMemLoc(vault);
  //Serial.print("MEMORY LOC FOR VAULT TO RESET");
  //Serial.println(vaultMem);
  if (vault > 104 && vault < 121)
  {
    //Reset registered card
    EEPROM.write(vaultMem, 0xFF);
    EEPROM.write(vaultMem + 1, 0xFF);
    EEPROM.write(vaultMem + 2, 0xFF);
    EEPROM.write(vaultMem + 3, 0xFF);
    int passMem = EEPROM.read(vaultMem + 4);

    //Reset registered password
    EEPROM.write(passMem, 0xFF);
    EEPROM.write(passMem + 1, 0xFF);
    EEPROM.write(passMem + 2, 0xFF);

    //Reset vault availability
    EEPROM.write(vault + 95, 1);
  }
  else
  {
    setLCDtext("Not a vault");
  }
}

