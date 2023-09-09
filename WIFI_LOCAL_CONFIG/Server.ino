void Interrupt(void *parameter) {
  while (1) {
    if (start_init == true) {
      WiFi.mode(WIFI_AP);
      IPAddress localIP(192, 168, 1, 1);
      IPAddress gateway(192, 168, 1, 1);
      IPAddress subnet(255, 255, 255, 0);
      WiFi.softAPConfig(localIP, gateway, subnet);
      WiFi.softAP("ESP32-WebServer", "12345678");
      ArduinoOTA.setHostname("ESP32-OTA");
      ArduinoOTA.begin();

      // Setup web server
      String html = String(htmlContent); // Copy the HTML content to a String
      // Read values from EEPROM
      String value1 = readFromEEPROM(0);
      String value2 = readFromEEPROM(20);
      String value3 = readFromEEPROM(40);
      String value4 = readFromEEPROM(80);
      String value5 = readFromEEPROM(100);
      String value6 = readFromEEPROM(120);
      String value7 = readFromEEPROM(160);
      String value8 = readFromEEPROM(200);
      String value9 = readFromEEPROM(220);
      String value10 = readFromEEPROM(240);
      String value11 = readFromEEPROM(260);
      String tempInput = readFromEEPROM(430);
      String humInput = readFromEEPROM(440);
      String customInput1 = readFromEEPROM(450);
      String customInput2 = readFromEEPROM(460);
      String customInput3 = readFromEEPROM(470);
      String customInput4 = readFromEEPROM(480);
      

      String modeSelect = readFromEEPROM(490);
      String classSelect = readFromEEPROM(510);
      String rs485Options = readFromEEPROM(500);

      html.replace("id=\"value1\"", "id=\"value1\" value=\"" + value1 + "\"");
      html.replace("id=\"value2\"", "id=\"value2\" value=\"" + value2 + "\"");
      html.replace("id=\"value3\"", "id=\"value3\" value=\"" + value3 + "\"");
      html.replace("id=\"value4\"", "id=\"value4\" value=\"" + value4 + "\"");
      html.replace("id=\"value5\"", "id=\"value5\" value=\"" + value5 + "\"");
      html.replace("id=\"value6\"", "id=\"value6\" value=\"" + value6 + "\"");
      html.replace("id=\"value7\"", "id=\"value7\" value=\"" + value7 + "\"");
      html.replace("id=\"value8\"", "id=\"value8\" value=\"" + value8 + "\"");
      html.replace("id=\"value9\"", "id=\"value9\" value=\"" + value9 + "\"");
      html.replace("id=\"value10\"", "id=\"value10\" value=\"" + value10 + "\"");
      html.replace("id=\"value11\"", "id=\"value11\" value=\"" + value11 + "\"");
      html.replace("id=\"tempInput\"", "id=\"tempInput\" value=\"" + tempInput + "\"");
      html.replace("id=\"humInput\"", "id=\"humInput\" value=\"" + humInput + "\"");
      html.replace("id=\"customInput1\"", "id=\"customInput1\" value=\"" + customInput1 + "\"");
      html.replace("id=\"customInput2\"", "id=\"customInput2\" value=\"" + customInput2 + "\"");
      html.replace("id=\"customInput3\"", "id=\"customInput3\" value=\"" + customInput3 + "\"");
      html.replace("id=\"customInput4\"", "id=\"customInput4\" value=\"" + customInput4 + "\"");
      html.replace("id=\"modeSelect\"", "id=\"modeSelect\" value=\"" + modeSelect + "\"");
      html.replace("id=\"classSelect\"", "id=\"classSelect\" value=\"" + classSelect + "\"");
      html.replace("id=\"rs485Options\"", "id=\"rs485Options\" value=\"" + rs485Options + "\"");

      dnsServer.start(DNS_PORT, "*", localIP);
      server.onNotFound([html]() {
        server.send(200, "text/html", html);
      });
      server.on("/process", HTTP_POST, handleProcess);
      server.on("/update", HTTP_GET, handleFirmwareUpdate);
      server.on("/update", HTTP_POST, []() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        ESP.restart();
      });
      server.begin();
      start_init = false;
    }
    ArduinoOTA.handle();
    if (webServerEnabled) {
      dnsServer.processNextRequest();
      server.handleClient();
    }
    if (dataSent) {
      dataSent = false;
    } vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
