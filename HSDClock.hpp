#pragma once

#include "HSDConfig.hpp"
#include <TM1637.h>
#include <time.h>

class HSDClock
{
public:

  HSDClock(const HSDConfig& config);

  void begin();
  void handle();

  time_t now;
  struct tm * timeinfo;

private:

  const HSDConfig& m_config;

  uint8_t new_time;
  uint8_t old_time;
  time_t last_ntp_update;

  int8_t TimeDisp[4];
  TM1637 m_tm1637;
};

