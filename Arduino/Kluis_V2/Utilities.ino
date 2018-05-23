/**@file Utilities.ino*/
int vaultToMemLoc(int vaultnr)
{
  int vaultMem = vaultnr - VAULTMEMOFFSET;
  vaultMem = (vaultMem * 5) + 2000;
  return vaultMem;
}

bool isNumeric(char val)
{
  if (val == '1' || val == '2' || val == '3' || val == '4' || val == '5' || val == '6' || val == '7' || val == '8' || val == '9' || val == '0')
  {
    return true;
  }
  else
  {
    return false;
  }
}

