#include "HomeStatusDisplay.h"

static const char* VERSION = "0.5_dev";
static const char* IDENTIFIER = "HomeStatusDisplay";

HomeStatusDisplay display;

void setup() 
{ 
  display.begin(VERSION, IDENTIFIER);
}

void loop() 
{     
  display.work();
}

