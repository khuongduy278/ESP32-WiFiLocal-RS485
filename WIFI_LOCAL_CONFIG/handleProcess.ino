void handleProcess() {
  String value1 = server.arg("value1");
  String value2 = server.arg("value2");
  String value3 = server.arg("value3");
  String value4 = server.arg("value4");
  String value5 = server.arg("value5");
  String value6 = server.arg("value6");
  String value7 = server.arg("value7");
  String value8 = server.arg("value8");
  String value9 = server.arg("value9");
  String value10 = server.arg("value10");
  String value11 = server.arg("value11");
  String value12 = server.arg("value12");
  String value13 = server.arg("value13");
  String value14 = server.arg("value14");
  String value15 = server.arg("value15");
  String value16 = server.arg("value16");
  String value17 = server.arg("value17");
  String value18 = server.arg("value18");
  String value19 = server.arg("value19");
  String value20 = server.arg("value20");
  String value21 = server.arg("value21");
  String TempInput = server.arg("tempInput");
  String HumInput = server.arg("humInput");
  String customInput1 = server.arg("customInput1");
  String customInput2 = server.arg("customInput2");
  String customInput3 = server.arg("customInput3");
  String customInput4 = server.arg("customInput4");

  Mode = server.arg("modeSelect");
  Class = server.arg("classSelect");
  RS485_OPTIONS = server.arg("rs485Options");
  String data1 = server.arg("dataType1");
  String data2 = server.arg("dataType2");
  String data3 = server.arg("dataType3");
  String data4 = server.arg("dataType4");
  String data5 = server.arg("dataType5");

  server.send(200, "text/plain", "OK");
  dataSent = true;

  saveToEEPROM(0, value1);
  saveToEEPROM(20, value2);
  saveToEEPROM(40, value3);
  saveToEEPROM(80, value4);
  saveToEEPROM(100, value5);
  saveToEEPROM(120, value6);
  saveToEEPROM(160, value7);
  saveToEEPROM(200, value8);
  saveToEEPROM(220, value9);
  saveToEEPROM(240, value10);
  saveToEEPROM(260, value11);
  saveToEEPROM(280, value12);
  saveToEEPROM(300, value13);
  saveToEEPROM(310, value14);
  saveToEEPROM(330, value15);
  saveToEEPROM(340, value16);
  saveToEEPROM(360, value17);
  saveToEEPROM(370, value18);
  saveToEEPROM(390, value19);
  saveToEEPROM(400, value20);
  saveToEEPROM(420, value21);
  saveToEEPROM(430, TempInput);
  saveToEEPROM(440, HumInput);
  saveToEEPROM(450, customInput1);
  saveToEEPROM(460, customInput2);
  saveToEEPROM(470, customInput3);
  saveToEEPROM(480, customInput4);
  
  saveToEEPROM(290, data1);
  saveToEEPROM(320, data2);
  saveToEEPROM(350, data3);
  saveToEEPROM(380, data4);
  saveToEEPROM(410, data5);
  saveToEEPROM(490, Mode);
  saveToEEPROM(500, RS485_OPTIONS);
  saveToEEPROM(510, Class);

  Serial.println("Data saved to EEPROM successfully.");

  webServerEnabled = false;
  server.stop();
  WiFi.disconnect();
  Serial.println("Disconnected from Wi-Fi_ESP32-WebServer");
  ESP.restart();
}
