#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <Crc16.h>
#include <math.h>
#include <Ticker.h>
#include <lorawan.h>
#include <Update.h>
#include <ArduinoOTA.h>
#include <DNSServer.h>

Ticker timer;
Ticker timer1;
Crc16 crc;

DNSServer dnsServer;
WebServer server(80);

const sRFM_pins RFM_pins {
  .CS = 15,
  .RST = 33,
  .DIO0 = 32,
  .DIO1 = 35,
  .DIO2 = 23,
  .DIO5 = 23,
};
String Mode = "";
String Class = "";
String RS485_OPTIONS = "";

String DEV_EUI = "";
String APP_EUI = "";
String APPS_KEY_OTAA = "";
String INTERVAL_OTAA = "";

String DEV_ADDR = "";
String NWSK = "";
String APPS_KEY_ABP = "";
String INTERVAL_ABP = "";

String BaudRates_Customize = "";
String ByteSend_Customize = "";
String RS485_Config_Customize = "";
String SWSERIAL;

String customInput1 = "";
String customInput2 = "";
String customInput3 = "";
String customInput4 = "";

String Device1 = "";
String Device2 = "";
String Device3 = "";
String Device4 = "";
String Device5 = "";

String DeviceValue1 = "";
String DeviceValue2 = "";
String DeviceValue3 = "";
String DeviceValue4 = "";
String DeviceValue5 = "";

String DataType1 = "";
String DataType2 = "";
String DataType3 = "";
String DataType4 = "";
String DataType5 = "";

String TempInput = "";
String HumInput = "";

float stepValue;
float Percentage;
float SensorValue;

/* LORAWAN downlink */
char outStr[255];
byte recvStatus = 0;
/***************************** RS485 *****************************/
int count_RS485 = 0;
int RS485_count = 0;
/* Declare RS485. */
#define RXD2 26
#define TXD2 27
#define RS485_PIN_DIR 25
#define RS485Transmit    HIGH
#define RS485Receive     LOW
SoftwareSerial RS485Serial(RXD2, TXD2);

uint8_t byteTemperature[6] = {};
uint8_t byteSend_RS485[8]  = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t byte_RS485[6]      = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t byteReceived_RS485[9];
int Hum, Temp;
float temperature_float = 0, humidity_float = 0;
String Data_Lorawan;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 500;

const byte DNS_PORT = 53;
const int buttonPin = 5;
int BaudRates;
bool buttonState = true;
bool webServerEnabled = false;
bool start_init = false;
bool dataSent = false;
bool rs485Enabled = true;
boolean State ;
bool sendLoraData = true; 
#define PIN_ANALOG 34

/***************************** Setup Variable and Pin *****************************/
/* Time variable. */
unsigned long Millis = 0;
unsigned long previousMillis_data = 0;
unsigned long interval_data; 
unsigned long previous_time = 0;
unsigned long previous_time_sensor = 0;
unsigned long previous_led = 0;
unsigned int counter = 0;    
unsigned int timer_previous = 0;

bool lora_connect = true;
bool lora_state = false;
bool rs485_state = true;
/***************************** Deepsleep Mode *****************************/
#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP 30
