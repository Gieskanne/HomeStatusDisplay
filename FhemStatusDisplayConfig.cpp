#include "FhemStatusDisplayConfig.h"
#include <FS.h>

static const char* configFileName = "/config.json";
static const char* version = "0.1_dev";
static const char* host = "FhemStatusDisplay";

FhemStatusDisplayConfig::FhemStatusDisplayConfig()
{  
  // TODO: reset all members
}

void FhemStatusDisplayConfig::begin()
{
  Serial.println("");
  Serial.println("Initializing config.");

  // TODO: read from config file
  setHost(host);

  setWifiSSID("xx");
  setWifiPSK("xx");

  setMqttServer("xx");
  setMqttStatusTopic("fhem/status/#");
  setMqttTestTopic("fhem/cmd/statusdisplay_01/test");  

  setNumberOfLeds(33);
  setLedDataPin(D2);
}

const char* FhemStatusDisplayConfig::getHost() const
{
  return m_cfgHost;
}

bool FhemStatusDisplayConfig::setHost(const char* host)
{
  strcpy(m_cfgHost, host);
  return true;
}

const char* FhemStatusDisplayConfig::getVersion() const
{
  return version;
}

const char* FhemStatusDisplayConfig::getWifiSSID() const
{
  return m_cfgWifiSSID;
}

bool FhemStatusDisplayConfig::setWifiSSID(const char* ssid)
{
  strcpy(m_cfgWifiSSID, ssid);
  return true;
}

const char* FhemStatusDisplayConfig::getWifiPSK() const
{
  return m_cfgWifiPSK;
}

bool FhemStatusDisplayConfig::setWifiPSK(const char* psk)
{
  strcpy(m_cfgWifiPSK, psk);
  return true;
}

const char* FhemStatusDisplayConfig::getMqttServer() const
{
  return m_cfgMqttServer;
}

bool FhemStatusDisplayConfig::setMqttServer(const char* ip)
{
  strcpy(m_cfgMqttServer, ip);
  return true;
}

const char* FhemStatusDisplayConfig::getMqttStatusTopic() const
{
  return m_cfgMqttStatusTopic;
}

bool FhemStatusDisplayConfig::setMqttStatusTopic(const char* topic)
{
  strcpy(m_cfgMqttStatusTopic, topic);
  return true;
}

const char* FhemStatusDisplayConfig::getMqttTestTopic() const
{
  return m_cfgMqttTestTopic;
}

bool FhemStatusDisplayConfig::setMqttTestTopic(const char* topic)
{
  strcpy(m_cfgMqttTestTopic, topic);
  return true;
}

uint32_t FhemStatusDisplayConfig::getNumberOfLeds() const
{
  return m_cfgNumberOfLeds;
}

void FhemStatusDisplayConfig::setNumberOfLeds(uint32_t numberOfLeds)
{
  m_cfgNumberOfLeds = numberOfLeds;
}

uint32_t FhemStatusDisplayConfig::getLedDataPin() const
{
  return m_cfgLedDataPin;
}

void FhemStatusDisplayConfig::setLedDataPin(uint32 dataPin)
{
  m_cfgLedDataPin = dataPin;
}

int FhemStatusDisplayConfig::getLedNumber(String deviceName, deviceType deviceType)
{
  int number = -1;

  for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(deviceMap); i++)
  {
    if(deviceName.equals(deviceMap[i].name) && (deviceType == deviceMap[i].type))
    {
      number = deviceMap[i].ledNumber;
      break;
    }
  }

  return number;
}

int FhemStatusDisplayConfig::getColorMapIndex(deviceType deviceType, String msg)
{
  int index = -1;

  for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(colorMap); i++)
  {
    if(msg.equals(colorMap[i].msg) && (deviceType == colorMap[i].type))
    {
      index = i;
      break;
    }
  }

  return index;
}

Led::Behavior FhemStatusDisplayConfig::getLedBehavior(int colorMapIndex)
{
  return colorMap[colorMapIndex].behavior;
}

Led::Color FhemStatusDisplayConfig::getLedColor(int colorMapIndex)
{
  return colorMap[colorMapIndex].color;
}

