#pragma once

#include "HSDConfigFile.hpp"
#include "PreAllocatedLinkedList.hpp"

// comment out next line if you do not need the clock module
#define CLOCK_ENABLED

#define JSON_KEY_HOST                  (F("host"))
#define JSON_KEY_WIFI_SSID             (F("wifiSSID"))
#define JSON_KEY_WIFI_PSK              (F("wifiPSK"))
#define JSON_KEY_MQTT_SERVER           (F("mqttServer"))
#define JSON_KEY_MQTT_USER             (F("mqttUser"))
#define JSON_KEY_MQTT_PASSWORD         (F("mqttPassword"))
#define JSON_KEY_MQTT_STATUS_TOPIC     (F("mqttStatusTopic"))
#define JSON_KEY_MQTT_TEST_TOPIC       (F("mqttTestTopic"))
#define JSON_KEY_MQTT_WILL_TOPIC       (F("mqttWillTopic"))
#define JSON_KEY_LED_COUNT             (F("ledCount"))
#define JSON_KEY_LED_PIN               (F("ledPin"))
#define JSON_KEY_LED_BRIGHTNESS        (F("ledBrightness"))
#define JSON_KEY_CLOCK_PIN_CLK         (F("clockCLK"))
#define JSON_KEY_CLOCK_PIN_DIO         (F("clockDIO"))
#define JSON_KEY_CLOCK_BRIGHTNESS      (F("clockBrightness"))
#define JSON_KEY_CLOCK_TIME_ZONE       (F("clockTZ"))
#define JSON_KEY_CLOCK_NTP_SERVER      (F("clockServer"))
#define JSON_KEY_CLOCK_NTP_INTERVAL    (F("clockInterval"))
#define JSON_KEY_COLORMAPPING_MSG      (F("m"))
#define JSON_KEY_COLORMAPPING_COLOR    (F("c"))
#define JSON_KEY_COLORMAPPING_BEHAVIOR (F("b"))
#define JSON_KEY_DEVICEMAPPING_NAME    (F("n"))
#define JSON_KEY_DEVICEMAPPING_LED     (F("l"))

#define NUMBER_OF_DEFAULT_COLORS       9

class HSDConfig
{
  
public:

  static const int MAX_DEVICE_MAPPING_NAME_LEN = 25;
  static const int MAX_COLOR_MAPPING_MSG_LEN = 15;
  
  /*
   * Enum which defines the different LED behaviors.
   */
  enum Behavior
  {
    OFF,
    ON,
    BLINKING,
    FLASHING,
    FLICKERING
  };

  /*
   * Defintion of default color names and hex values in a map like structure.
   */
  struct Map
  {
    char* key;
    uint32_t value; 
  };
   
  static const constexpr Map DefaultColor[NUMBER_OF_DEFAULT_COLORS] =
  {  
    {"NONE",   0x000000}, 
    {"GREEN",  0x00FF00},
    {"YELLOW", 0xFFCC00},
    {"ORANGE", 0xFF4400},
    {"RED",    0xFF0000},
    {"PURPLE", 0xFF00FF},
    {"BLUE",   0x0000FF},
    {"CYAN",   0x00FFFF},
    {"WHITE",  0xFFFFFF}
  };

  /*
   * This struct is used for mapping a device name to a led number, 
   * that means a specific position on the led stripe
   */
  struct DeviceMapping
  { 
    DeviceMapping()
    {
      memset(name, 0, MAX_DEVICE_MAPPING_NAME_LEN);
      ledNumber = 0;       
    }

    DeviceMapping(String n, int l)
    {
      strncpy(name, n.c_str(), MAX_DEVICE_MAPPING_NAME_LEN);
      name[MAX_DEVICE_MAPPING_NAME_LEN] = '\0';
      ledNumber = l;   
    }
    
    char name[MAX_DEVICE_MAPPING_NAME_LEN]; // name of the device
    int ledNumber;                          // led number on which reactions for this device are displayed
  };

  /*
   * This struct is used for mapping a message for a specific
   * message to a led behavior (see LedSwitcher::ledState).
   */
  struct ColorMapping
  {
    ColorMapping()
    {
      memset(msg, 0, MAX_COLOR_MAPPING_MSG_LEN);
      color = 0x000000;
      behavior = OFF;
    }
    
    ColorMapping(String m, uint32_t c, Behavior b)
    {
      strncpy(msg, m.c_str(), MAX_COLOR_MAPPING_MSG_LEN);
      msg[MAX_COLOR_MAPPING_MSG_LEN] = '\0';
      color = c;
      behavior = b;
    }
    
    char msg[MAX_COLOR_MAPPING_MSG_LEN+1];  // message 
    uint32_t color;                         // led color for message
    Behavior behavior;                      // led behavior for message
  };

  HSDConfig();

  void begin(const char* version, const char* defaultIdentifier);

  void saveMain();
  
  void saveColorMapping();
  void updateColorMapping();
  
  void saveDeviceMapping();
  void updateDeviceMapping();

  const char* getVersion() const;
  bool setVersion(const char* version);

  const char* getHost() const;
  bool setHost(const char* host);

  const char* getWifiSSID() const;
  bool setWifiSSID(const char* ssid);

  const char* getWifiPSK() const;
  bool setWifiPSK(const char* psk);

  const char* getMqttServer() const;
  bool setMqttServer(const char* ip);

  const char* getMqttUser() const;
  bool setMqttUser(const char* user);

  const char* getMqttPassword() const;
  bool setMqttPassword(const char* pwd);

  const char* getMqttStatusTopic() const;
  bool setMqttStatusTopic(const char* topic);

  const char* getMqttTestTopic() const;
  bool setMqttTestTopic(const char* topic);

  const char* getMqttWillTopic() const;
  bool setMqttWillTopic(const char* topic);

  uint8_t getNumberOfLeds() const;
  bool setNumberOfLeds(uint8_t numberOfLeds);

  uint8_t getLedDataPin() const;
  bool setLedDataPin(uint8_t dataPin);

  uint8_t getLedBrightness() const;
  bool setLedBrightness(uint8_t brightness);

  uint8_t getClockPinCLK() const;
  bool setClockPinCLK(uint8_t dataPin);

  uint8_t getClockPinDIO() const;
  bool setClockPinDIO(uint8_t dataPin);

  uint8_t getClockBrightness() const;
  bool setClockBrightness(uint8_t brightness);

  const char* getClockTimeZone() const;
  bool setClockTimeZone(const char* zone);

  const char* getClockNTPServer() const;
  bool setClockNTPServer(const char* server);

  uint16_t getClockNTPInterval() const;
  bool setClockNTPInterval(uint16_t minutes);

  void resetMainConfigData();
  void resetDeviceMappingConfigData();
  void resetColorMappingConfigData();

  int getNumberOfDeviceMappingEntries() const;
  int getNumberOfColorMappingEntries();
  
  bool addDeviceMappingEntry(int entryNum, String name, int ledNumber);
  bool deleteColorMappingEntry(int entryNum);
  bool deleteAllDeviceMappingEntries();
  bool isDeviceMappingDirty() const;
  bool isDeviceMappingFull() const;
  
  bool addColorMappingEntry(int entryNum, String msg, uint32_t color, Behavior behavior);
  bool deleteDeviceMappingEntry(int entryNum);
  bool deleteAllColorMappingEntries();
  bool isColorMappingDirty() const;
  bool isColorMappingFull() const;
  
  const DeviceMapping* getDeviceMapping(int index) const;
  const ColorMapping* getColorMapping(int index); 
    
  int getLedNumber(String device);
  String getDevice(int ledNumber);
  int getColorMapIndex(String msg);
  Behavior getLedBehavior(int colorMapIndex);
  uint32_t getLedColor(int colorMapIndex);
  
  uint32_t getDefaultColor(String key) const;
  String getDefaultColor(uint32_t value) const;
  String hex2string(uint32_t value) const;
  uint32_t string2hex(String value) const;

private:

  bool readMainConfigFile();
  void printMainConfigFile(JsonObject& json);
  void writeMainConfigFile();

  bool readColorMappingConfigFile();
  void writeColorMappingConfigFile();

  bool readDeviceMappingConfigFile();
  void writeDeviceMappingConfigFile();

  void onFileWriteError();

  static const int MAX_VERSION_LEN           = 20;
  static const int MAX_HOST_LEN              = 30;
  static const int MAX_WIFI_SSID_LEN         = 30;
  static const int MAX_WIFI_PSK_LEN          = 30;
  static const int MAX_MQTT_SERVER_LEN       = 20;
  static const int MAX_MQTT_USER_LEN         = 20;
  static const int MAX_MQTT_PASSWORD_LEN     = 50;
  static const int MAX_MQTT_STATUS_TOPIC_LEN = 50;
  static const int MAX_MQTT_TEST_TOPIC_LEN   = 50;
  static const int MAX_MQTT_WILL_TOPIC_LEN   = 50;
  static const int MAX_CLOCK_TIMEZONE_LEN    = 40;
  static const int MAX_CLOCK_NTP_SERVER_LEN  = 40;

  static const int MAX_COLOR_MAP_ENTRIES  = 30;
  static const int MAX_DEVICE_MAP_ENTRIES = 35;

  PreAllocatedLinkedList<ColorMapping> m_cfgColorMapping;
  bool m_cfgColorMappingDirty;

  PreAllocatedLinkedList<DeviceMapping> m_cfgDeviceMapping;
  bool m_cfgDeviceMappingDirty;
  
  char m_cfgVersion[MAX_VERSION_LEN + 1];
  char m_cfgHost[MAX_HOST_LEN + 1];
  char m_cfgWifiSSID[MAX_WIFI_SSID_LEN + 1];
  char m_cfgWifiPSK[MAX_WIFI_PSK_LEN + 1];
  char m_cfgMqttServer[MAX_MQTT_SERVER_LEN + 1];
  char m_cfgMqttUser[MAX_MQTT_USER_LEN + 1];
  char m_cfgMqttPassword[MAX_MQTT_PASSWORD_LEN + 1];
  char m_cfgMqttStatusTopic[MAX_MQTT_STATUS_TOPIC_LEN + 1];
  char m_cfgMqttTestTopic[MAX_MQTT_TEST_TOPIC_LEN + 1];
  char m_cfgMqttWillTopic[MAX_MQTT_WILL_TOPIC_LEN + 1];
  
  uint8_t m_cfgNumberOfLeds;
  uint8_t m_cfgLedDataPin;
  uint8_t m_cfgLedBrightness;

  uint8_t m_cfgClockPinCLK;
  uint8_t m_cfgClockPinDIO;
  uint8_t m_cfgClockBrightness;
  char m_cfgClockTimeZone[MAX_CLOCK_TIMEZONE_LEN + 1];
  char m_cfgClockNTPServer[MAX_CLOCK_NTP_SERVER_LEN + 1];
  uint16_t m_cfgClockNTPInterval;

  HSDConfigFile m_mainConfigFile;
  HSDConfigFile m_colorMappingConfigFile;
  HSDConfigFile m_deviceMappingConfigFile;
};
