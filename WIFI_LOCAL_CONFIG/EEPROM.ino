void saveToEEPROM(int address, String value)
{
  for (int i = 0; i < value.length(); ++i)
  {
    EEPROM.write(address + i, value[i]);
  }
  EEPROM.write(address + value.length(), 0); // Null terminator
  EEPROM.commit();
}

String readFromEEPROM(int address)
{
  String value = "";
  for (int i = 0; i < 50; ++i)
  {
    byte byteValue = EEPROM.read(address + i);
    if (byteValue == 0)
    {
      break;
    }
    value += char(byteValue);
  }
  return value;
}

void Read_Eui_From_EEPROM()
{
  // ===== EEPROM OTAA ====//
  for (int i = 0; i < 20; ++i)
  {
    DEV_EUI += char(EEPROM.read(i));
  }
  DEV_EUI.remove(DEV_EUI.indexOf(0));
  for (int i = 20; i < 40; ++i)
  {
    APP_EUI += char(EEPROM.read(i));
  }
  APP_EUI.remove(APP_EUI.indexOf(0));
  for (int i = 40; i < 80; ++i)
  {
    APPS_KEY_OTAA += char(EEPROM.read(i));
  }
  APPS_KEY_OTAA.remove(APPS_KEY_OTAA.indexOf(0));
  for (int i = 80; i < 100; ++i)
  {
    INTERVAL_OTAA += char(EEPROM.read(i));
  }
  INTERVAL_OTAA.remove(INTERVAL_OTAA.indexOf(0));


  // ======= EEPROM ABP ========//
  for (int i = 100; i < 120; ++i)
  {
    DEV_ADDR += char(EEPROM.read(i));
  }
  DEV_ADDR.remove(DEV_ADDR.indexOf(0));
  for (int i = 120; i < 160 ; ++i)
  {
    NWSK += char(EEPROM.read(i));
  }
  NWSK.remove(NWSK.indexOf(0));

  for (int i = 160; i < 200; ++i)
  {
    APPS_KEY_ABP += char(EEPROM.read(i));
  }
  APPS_KEY_ABP.remove(APPS_KEY_ABP.indexOf(0));
  for (int i = 200; i < 220; ++i)
  {
    INTERVAL_ABP += char(EEPROM.read(i));
  }
  INTERVAL_ABP.remove(INTERVAL_ABP.indexOf(0));


  // ======== Customize ===========//
  for (int i = 220; i < 240; ++i)
  {
    BaudRates_Customize += char(EEPROM.read(i));
  }
  BaudRates_Customize.remove(BaudRates_Customize.indexOf(0));
  for (int i = 240; i < 260; ++i)
  {
    ByteSend_Customize += char(EEPROM.read(i));
  }
  ByteSend_Customize.remove(ByteSend_Customize.indexOf(0));
  for (int i = 260; i < 280; ++i)
  {
    RS485_Config_Customize += char(EEPROM.read(i));
  }
  RS485_Config_Customize.remove(RS485_Config_Customize.indexOf(0));

  //====== DataSend===========//
  for (int i = 280; i < 290; ++i)
  {
    Device1 += char(EEPROM.read(i));
  }
  Device1.remove(Device1.indexOf(0));
  for (int i = 290; i < 300; ++i)
  {
    DataType1 += char(EEPROM.read(i));
  }
  DataType1.remove(DataType1.indexOf(0));
  for (int i = 300; i < 310; ++i)
  {
    DeviceValue1 += char(EEPROM.read(i));
  }
  DeviceValue1.remove(DeviceValue1.indexOf(0));
  for (int i = 310; i < 320; ++i)
  {
    Device2 += char(EEPROM.read(i));
  }
  Device2.remove(Device2.indexOf(0));
  for (int i = 320; i < 330; ++i)
  {
    DataType2 += char(EEPROM.read(i));
  }
  DataType2.remove(DataType2.indexOf(0));
  for (int i = 330; i < 340; ++i)
  {
    DeviceValue2 += char(EEPROM.read(i));
  }
  DeviceValue2.remove(DeviceValue2.indexOf(0));
  for (int i = 340; i < 350; ++i)
  {
    Device3 += char(EEPROM.read(i));
  }
  Device3.remove(Device3.indexOf(0));
  for (int i = 350; i < 360; ++i)
  {
    DataType3 += char(EEPROM.read(i));
  }
  DataType3.remove(DataType3.indexOf(0));
  for (int i = 360; i < 370; ++i)
  {
    DeviceValue3 += char(EEPROM.read(i));
  }
  DeviceValue3.remove(DeviceValue3.indexOf(0));

  for (int i = 370; i < 380; ++i)
  {
    Device4 += char(EEPROM.read(i));
  }
  Device4.remove(Device4.indexOf(0));
  for (int i = 380; i < 390; ++i)
  {
    DataType4 += char(EEPROM.read(i));
  }
  DataType4.remove(DataType4.indexOf(0));
  for (int i = 390; i < 400; ++i)
  {
    DeviceValue4 += char(EEPROM.read(i));
  }
  DeviceValue4.remove(DeviceValue4.indexOf(0));
  for (int i = 400; i < 410; ++i)
  {
    Device5 += char(EEPROM.read(i));
  }
  Device5.remove(Device5.indexOf(0));
  for (int i = 410; i < 420; ++i)
  {
    DataType5 += char(EEPROM.read(i));
  }
  DataType5.remove(DataType5.indexOf(0));
  for (int i = 420; i < 430; ++i)
  {
    DeviceValue5 += char(EEPROM.read(i));
  }
  DeviceValue5.remove(DeviceValue5.indexOf(0));

  // ======== Name Data Temp/Hum ======//
  for (int i = 430; i < 440; ++i)
  {
    TempInput += char(EEPROM.read(i));
  }
  TempInput.remove(TempInput.indexOf(0));
  for (int i = 440; i < 450 ; ++i)
  {
    HumInput += char(EEPROM.read(i));
  }
  HumInput.remove(HumInput.indexOf(0));

  for (int i = 450; i < 460; ++i)
  {
    customInput1 += char(EEPROM.read(i));
  }
  customInput1.remove(customInput1.indexOf(0));
  for (int i = 460; i < 470 ; ++i)
  {
    customInput2 += char(EEPROM.read(i));
  }
  customInput2.remove(customInput2.indexOf(0));
  for (int i = 470; i < 480; ++i)
  {
    customInput3 += char(EEPROM.read(i));
  }
  customInput3.remove(customInput3.indexOf(0));
  for (int i = 480; i < 490 ; ++i)
  {
    customInput4 += char(EEPROM.read(i));
  }
  customInput4.remove(customInput4.indexOf(0));


  // ======== MODE AND CLASS AND RS485======//
  for (int i = 490; i < 500; ++i)
  {
    Mode += char(EEPROM.read(i));
  }
  Mode.remove(Mode.indexOf(0));

  for (int i = 510; i < 515; ++i)
  {
    Class += char(EEPROM.read(i));
  }
  Class.remove(Class.indexOf(0));

  for (int i = 500; i < 510; ++i)
  {
    RS485_OPTIONS += char(EEPROM.read(i));
  }
  RS485_OPTIONS.remove(RS485_OPTIONS.indexOf(0));
}
