#include "FhemStatusDisplayWebServer.h"
#include <ESP8266mDNS.h>

FhemStatusDisplayWebServer::FhemStatusDisplayWebServer(FhemStatusDisplayConfig& config)
:
m_server(80),
m_config(config)
{
  m_updateServer.setup(&m_server);
}

void FhemStatusDisplayWebServer::begin()
{
  Serial.println("");
  Serial.println("Starting WebServer.");

  MDNS.begin(m_config.getHost());
  m_server.begin();
  MDNS.addService("http", "tcp", 80);
  m_server.on("/", std::bind(&FhemStatusDisplayWebServer::deliverRootPage, this));
  m_server.onNotFound(std::bind(&FhemStatusDisplayWebServer::deliverNotFoundPage, this));
}

void FhemStatusDisplayWebServer::handleClient()
{
  m_server.handleClient();
}

void FhemStatusDisplayWebServer::deliverRootPage()
{
  //bool needSave = updateConfig();
  
  String html = ""
  "<!doctype html> <html>"
  "<head> <meta charset='utf-8'>"
  "<title>" + String(m_config.getHost()) + " Configuration</title>"
  "</head>"
  "<body bgcolor='#F0F0F0'><font face='Verdana,Arial,Helvetica'>"
  "<b><h1>" + m_config.getHost() + " Configuration</h1></b>"
  "<h4>Software version: " + m_config.getVersion() + "</h4>";
 
  if (WiFi.status() == WL_CONNECTED)
  {
    html += "ESP8266 is connected to WLAN <b>" + WiFi.SSID() + "</b> and has IP <b>" + ip2String(WiFi.localIP()) + "</b>.<br/><br/>";
  }
  else
  {
    html += "ESP8266 ist not connected to local network yet.<br/><br/>";
  }

  html += ""
  "<form><font face='Verdana,Arial,Helvetica'>";

  html += ""
  "<table width='30%' border='0' cellpadding='0' cellspacing='2'>"
  " <tr>"
  "  <td><b><font size='+1'>General</font></b></td>"
  "  <td></td>"
  " </tr>"
  " <tr>"
  "  <td>Host name</td>"
  "  <td><input type='text' id='host' name='host' value='" + String(m_config.getHost()) + "' size='30' maxlength='40' placeholder='SSID'></td>"
  " </tr>";

  html += ""
  " <tr>"
  "  <td><b><font size='+1'>WiFi</font></b></td>"
  "  <td></td>"
  " </tr>"
  " <tr>"
  "  <td>SSID</td>"
  "  <td><input type='text' id='wifiSSID' name='wifiSSID' value='" + String(m_config.getWifiSSID()) + "' size='30' maxlength='40' placeholder='SSID'></td>"
  " </tr>"
  " <tr>"
  "  <td>Password</td>"
  "  <td><input type='text' id='wifiPSK' name='wifiPSK' value='" + String(m_config.getWifiPSK()) + "' size='30' maxlength='40' placeholder='Password'></td>"
  " </tr>";

  html += ""
  " <tr>"
  "  <td><b><font size='+1'>MQTT</font></b></td>"
  "  <td></td>"
  " </tr>"
  " <tr>"
  "  <td>Server</td>"
  "  <td><input type='text' id='mqttServer' name='mqttServer' value='" + String(m_config.getMqttServer()) + "' size='30' maxlength='40' placeholder='IP Address'></td>"
  " </tr>"
  " <tr>"
  "  <td>Status topic</td>"
  "  <td><input type='text' id='mqttStatusTopic' name='mqttStatusTopic' value='" + String(m_config.getMqttStatusTopic()) + "' size='30' maxlength='40' placeholder='#'></td>"
  " </tr>"
  " <tr>"
  "  <td>Test topic</td>"
  "  <td><input type='text' id='mqttTestTopic' name='mqttTestTopic' value='" + String(m_config.getMqttTestTopic()) + "' size='30' maxlength='40' placeholder='#'></td>"
  " </tr>";

  html += ""
  " <tr>"
  "  <td><b><font size='+1'>LEDs</font></b></td>"
  "  <td></td>"
  " </tr>"
  " <tr>"
  "  <td>Number of LEDs</td>"
  "  <td><input type='text' id='numberOfLeds' name='numberOfLeds' value='" + String(m_config.getNumberOfLeds()) + "' size='30' maxlength='40' placeholder='1'></td>"
  " </tr>"
  " <tr>"
  "  <td>LED pin</td>"
  "  <td><input type='text' id='ledPin' name='ledPin' value='" + String(m_config.getLedDataPin()) + "' size='30' maxlength='40' placeholder='#'></td>"
  " </tr>";

  html += ""
  " <tr>"
  "  <td></td>"
  "  <td></td>"
  " </tr>"
  " <tr>"
  "  <td></td>"
  "  <td><input type='submit' value='Save' style='height:30px; width:200px' ></td>"
  " </tr>";

  html += ""
  " <tr>"
  "  <td></td>"
  "  <td></td>"
  " </tr>"
  " <tr>"
  "  <td></td>"
  "  <td><input type='submit' value='Reboot' id='reset' name='reset' value='' style='height:30px; width:200px'></td>"
  " </tr>";

  html += ""
  " <tr>"
  "  <td></td>"
  "  <td></td>"
  " </tr>"
  " <tr>"
  "  <td></td>"
  "  <td><input type='button' onclick=\"location.href='./update'\"  value='Update Firmware' style='height:30px; width:200px' ></td>"
  " </tr>";
  
  html += ""
  "</table>";

  html += ""
  "</form>";
  
  html += ""
  "</font></body></html>";

  m_server.send(200, "text/html", html);
/*
  if(needSave)
  {
    Serial.println("Config has changed, storing it.");
    m_config.save();
  }

  if(m_server.hasArg("reset")) 
  {
    Serial.println("Rebooting ESP.");
    ESP.restart();
  }*/
}

void FhemStatusDisplayWebServer::deliverNotFoundPage()
{
  String html = "File Not Found\n\n";
  html += "URI: ";
  html += m_server.uri();
  html += "\nMethod: ";
  html += (m_server.method() == HTTP_GET)?"GET":"POST";
  html += "\nArguments: ";
  html += m_server.args();
  html += "\n";
  
  for (uint8_t i = 0; i < m_server.args(); i++)
  {
    html += " " + m_server.argName(i) + ": " + m_server.arg(i) + "\n";
  }
  
  m_server.send(404, "text/plain", html);
}

String FhemStatusDisplayWebServer::ip2String(IPAddress ip)
{
  char buffer[20];
  memset(buffer, 0, sizeof(buffer));

  sprintf(buffer,"%d.%d.%d.%d", ip[0],ip[1],ip[2],ip[3]);
  
  return String(buffer);
}

bool FhemStatusDisplayWebServer::updateConfig()
{
  bool needSave = false;

  if (m_server.hasArg("host"))
  {
    needSave |= m_config.setHost(m_server.arg("host").c_str());
  }
  
  if (m_server.hasArg("wifiSSID"))
  {
    needSave |= m_config.setWifiSSID(m_server.arg("wifiSSID").c_str());
  }
  
  if (m_server.hasArg("wifiPSK")) 
  {
    needSave |= m_config.setWifiPSK(m_server.arg("wifiPSK").c_str());
  }

  return needSave;
}

