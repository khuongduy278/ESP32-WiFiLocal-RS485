/*Function RS485*/
void readRS485()
{
  for (int i = 0; i < sizeof(byteTemperature); i++)
  {
    byte_RS485[i] = byteTemperature[i];
  }
  CRC_RS485_return();
  delay(10);
  RS485();
  delay(10);
  if (byteReceived_RS485[0] == 0x01 && byteReceived_RS485[1] ==  0x03 && byteReceived_RS485[2] ==  0x04 )
  {
    if (RS485_OPTIONS == "Temp/Hum" || RS485_OPTIONS == "PH") {
      Hum = (byteReceived_RS485[3] << 8 ) + byteReceived_RS485[4];
      int Temp1  = (byteReceived_RS485[5] << 8 ) + byteReceived_RS485[6];
      Temp = hexToDecimal(Temp1);
      if (Temp > -300 && Temp < 500)
      {
        Serial.print("Temp"); Serial.println(float(Temp / 10));
        Serial.print("Hum"); Serial.println(float(Hum / 10));
        temperature_float = float(Temp / 10.0);
        humidity_float = float(Hum / 10.0);
      }
    } else if (byteReceived_RS485[0] == 0x00 && byteReceived_RS485[1] ==  0x00 && byteReceived_RS485[2] ==  0x00 )
    {
      Hum = (byteReceived_RS485[3] << 8 ) + byteReceived_RS485[4];
      Temp  = (byteReceived_RS485[5] << 8 ) + byteReceived_RS485[6];
      temperature_float = float(Temp / 10.0);
      humidity_float = float(Hum / 10.0);
      count_RS485++;
      if (count_RS485 == 5)
      {
        rs485_state = false;
      }
    } else {
      String Input1 = readFromEEPROM(460).substring(0, readFromEEPROM(460).indexOf(','));
      String Input2 = readFromEEPROM(460).substring(0, readFromEEPROM(460).indexOf(',') + 1);
      String Input3 = readFromEEPROM(480).substring(0, readFromEEPROM(480).indexOf(','));
      String Input4 = readFromEEPROM(480).substring(readFromEEPROM(480).indexOf(',') + 1);

      int index_customInput1 = Input1.toInt();
      int index_customInput2 = Input2.toInt();
      int index_customInput3 = Input3.toInt();
      int index_customInput4 = Input4.toInt();

      Hum = (byteReceived_RS485[(index_customInput1)] << 8 ) + byteReceived_RS485[(index_customInput2)];
      int Temp1  = (byteReceived_RS485[index_customInput3] << 8 ) + byteReceived_RS485[(index_customInput4)];
      Temp = hexToDecimal(Temp1);
      Serial.print(customInput3); Serial.print(":");Serial.print(" "); Serial.println(float(Temp / 10));
      Serial.print(customInput1); Serial.print(":");Serial.print(" "); Serial.println(float(Hum / 10));
      temperature_float = float(Temp / 10.0);
      humidity_float = float(Hum / 10.0);
      rs485_state = true;
      count_RS485 = 0;
    }
  }
}
void RS485(void)
{
  digitalWrite(RS485_PIN_DIR, RS485Transmit);
  Serial.print("send:");
  for (int i = 0; i < sizeof(byteSend_RS485); i++)
  {
    RS485Serial.write(byteSend_RS485[i]);
    Serial.print(byteSend_RS485[i], HEX);
    Serial.print(" ");
  }
  Serial.println("");
  digitalWrite(RS485_PIN_DIR, RS485Receive);
  if (RS485Serial.available())
  {
    RS485_count = 0;
    Serial.println("received:");
    for (int i = 0; i < sizeof(byteReceived_RS485); i++)
    {
      byteReceived_RS485[i] = RS485Serial.read();
      Serial.print(byteReceived_RS485[i], HEX);
      Serial.print(" ");
    }
    Serial.println("");
    digitalWrite(RS485_PIN_DIR, RS485Transmit);
  }
  else
  {
    RS485_count++;
    if (RS485_count > 2)
    {
      for (int i = 0; i < sizeof(byteReceived_RS485); i++)
      {
        byteReceived_RS485[i] = 0x00;
      }
    }
  }
}
void CRC_RS485_return()
{
  crc.clearCrc();
  for (byte i = 0; i < 6; i++)
  {
    crc.updateCrc(byte_RS485[i]);
  }
  long crc_return = crc.getCrc();
  crc_return = crc.Modbus(byte_RS485, 0, 6);
  union {
    unsigned long value_crc;
    unsigned char bytes[2];
  } CurrentPosition;
  CurrentPosition.value_crc = crc_return;
  for (int i = 0; i < sizeof(byteSend_RS485); i++)
  {
    if (i == 6 || i == 7)
    {
      byteSend_RS485[i] = CurrentPosition.bytes[i - 6];
    }
    else
    {
      byteSend_RS485[i] = byte_RS485[i];
    }
  }
}
int hexToDecimal(int hexString) {
  int Temp = hexString;
  if (hexString > 32768) {
    Serial.println(Temp);
    Temp = -(1 << (4 * 4)) + Temp;
  }
  return Temp;
}
