#include <stdio.h>
#include "FastLED.h"
#include <iostream>

#define BoardPin A4 //G32
#define BoardWidth 32
#define BoardHeight 8
#define LED_NUM BoardWidth*BoardHeight

#define COLOR_ORDER RGB
#define CHIPSET WS2811
#define BRIGHTNESS 250
#define LED_TYPE WS2812