#include <Arduino.h>
#include "config.h"

uint32_t configVersion = 3113834692; //generated identifier to compare config with EEPROM

const configData defaults PROGMEM =
{
	100,
