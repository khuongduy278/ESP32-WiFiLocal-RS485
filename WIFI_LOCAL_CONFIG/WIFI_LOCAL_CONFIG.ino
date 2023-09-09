#include "main.h"
#include "HTML.h"
#include "FreeRTOS.h"

void Read_Temp (void *parameter)
{
  while (1)
  {
    if (rs485Enabled) {
      if (millis() - previous_time_sensor > interval_data)
      {
        readRS485();
        previous_time_sensor = millis();
      } vTaskDelay(50 / portTICK_PERIOD_MS);
    }
  }
}
void Send_Data_To_Server(void *parameter )
{
  while (1)
  {
    if (sendLoraData) {
      if (millis() - previousMillis_data > interval_data) {
        uplink_lorawan();
        previousMillis_data = millis();
        vTaskDelay(100 / portTICK_PERIOD_MS);
      }
      recvStatus = lora.readData(outStr);
      if (recvStatus) {
        Serial.println(outStr);
      }
      lora.update();
      vTaskDelay(50 / portTICK_PERIOD_MS);
    }
  }
}

void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);
  pinMode(buttonPin, INPUT);
  pinMode(RS485_PIN_DIR, OUTPUT);
  digitalWrite(RS485_PIN_DIR, RS485Transmit);
  Serial.println("Start");
  Read_Eui_From_EEPROM();
  delay(1000);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING);

  Serial.println("Mode:" + readFromEEPROM(490));
  Serial.println("Class:" + readFromEEPROM(510));
  Serial.println("RS485_OPTIONS:" + readFromEEPROM(500));

  if (readFromEEPROM(480).length() > 0) {
    if (Mode == "OTAA") {
      Serial.println("DEV EUI: " + readFromEEPROM(0));
      Serial.println("APP EUI: " + readFromEEPROM(20));
      Serial.println("APPS KEY OTAA: " + readFromEEPROM(40));
      Serial.println("Intenval_OTAA: " + readFromEEPROM(80));
      int intervalValue = readFromEEPROM(80).toInt();
      interval_data = intervalValue * 1000;

    } else {
      Serial.println("DEV ADDR: " + readFromEEPROM(100));
      Serial.println("NWSK: " + readFromEEPROM(120));
      Serial.println("APPS KEY ABP: " + readFromEEPROM(160));
      Serial.println("Intenval_ABP: " + readFromEEPROM(200));
      int intervalValue = readFromEEPROM(200).toInt();
      interval_data = intervalValue * 1000;
    }
  } else {
    interval_data = 3000;
  }

  if (readFromEEPROM(500).length() > 0) {
    if (readFromEEPROM(500) == "Temp/Hum" || readFromEEPROM(500) == "PH")
    {
      uint8_t tempArray[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02};
      memcpy(byteTemperature, tempArray, sizeof(tempArray));
      BaudRates = 4800;
      SWSERIAL = SWSERIAL_8N1;
    } else {
      int index_customInput2 = customInput2.toInt();
      int index_customInput4 = customInput4.toInt();
      Serial.println("BaudRates_Customize: " + readFromEEPROM(220));
      Serial.println("ByteSend_Customize: " + readFromEEPROM(240));
      Serial.println("RS485_Config_Customize: " + readFromEEPROM(260));
      BaudRates = readFromEEPROM(220).toInt();
      if (readFromEEPROM(260).length() > 0) {
        String PDS = readFromEEPROM(260); // Parity + dataBits + stopBits
        SWSERIAL = "SWSERIAL_" + PDS;
        if (SWSERIAL.startsWith("SWSERIAL_")) {
          SWSERIAL = SWSERIAL.substring(10); //(SWSERIAL_)
        }
      }
    }
  } else {
    BaudRates = 4800;
  }

  for (int i = 0; i < 5; i++)
  {
    int address = 280 + i * 30;
    String key = readFromEEPROM(address);
    if (readFromEEPROM(address).length() > 0)
      if (key.length() > 0) {
        String dataType = readFromEEPROM(address + 10);
        String dataValue = readFromEEPROM(address + 20);

        if (dataType == "Digital") {
          int pinNumber = readFromEEPROM(address + 20).toInt();
          pinMode(pinNumber, INPUT);
          int pinState = digitalRead(pinNumber);
          String stateString = (pinState == HIGH) ? "true" : "false";
          Serial.print(key); Serial.println(" : " + stateString);
        }
        else if (dataType == "Analog") {
          String valuePart1 = dataValue.substring(0, dataValue.indexOf(','));
          String valuePart2 = dataValue.substring(dataValue.indexOf(',') + 1);

          int xValue = valuePart1.toInt();
          int yValue = valuePart2.toInt();

          stepValue = float(yValue - xValue) / 4095.0;
          //          int readAnalog = analogRead(PIN_ANALOG);
          float readAnalog = 1000;
          Percentage = float (readAnalog / 4095) * 100;
          SensorValue = readAnalog * stepValue + float(xValue) ;

          Serial.print(key); Serial.print(" : " ); Serial.print(Percentage); Serial.println(" % " );
          Serial.print(key); Serial.print(" : "); Serial.println(SensorValue);
        } else {
          Serial.print(key);
          Serial.print(" : ");
          Serial.println(dataValue);
        }
      }
  }
  //    RS485Serial.begin(4800, SWSERIAL_8N1);
  RS485Serial.begin(BaudRates);
  RS485Serial.write(SWSERIAL.c_str());
  Convert_RS485();
  setup_lora();

  xTaskCreatePinnedToCore(Interrupt, "Task1", 8000, NULL, 1, &Interrupt_p, 1);
  xTaskCreatePinnedToCore(Read_Temp, "Task2", 4000, NULL, 1, &Read_Temp_p, 0);
  xTaskCreatePinnedToCore(Send_Data_To_Server, "Task3", 6000, NULL, 1, &Send_Data_To_Server_p, 0);
  disableCore0WDT();
}

void loop() {
}
