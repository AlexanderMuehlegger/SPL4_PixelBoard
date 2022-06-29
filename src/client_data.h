#include <stdio.h>
#include "FastLED.h"
#include <iostream>
#include <Bounce2.h>
#include <OneButton.h>

#include <LEDMatrix.h>
#include <LEDText.h>
#include <FontMatrise.h>

#define BoardPin A4 //G32
#define BoardPin2 33
#define BoardWidth 32
#define BoardHeight 8
#define MatrixWidth 32
#define MatrixHeight -8
#define LED_NUM BoardWidth*BoardHeight

#define COLOR_ORDER RGB
#define CHIPSET WS2811
#define BRIGHTNESS 250
#define LED_TYPE WS2812
#define MATRIX_TYPE    HORIZONTAL_ZIGZAG_MATRIX

#define MAX_STARTUP_TIME 60000 // 5 min || 1 min = 60000

#define Swtich_Button 21