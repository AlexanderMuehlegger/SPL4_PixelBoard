// #include <client_data.h>

// CRGB leds_plus_safety_pixel[LED_NUM + 1];
// CRGB *const leds(leds_plus_safety_pixel + 1);

// bool startup_completed = false;
// Bounce bouncer = Bounce(Swtich_Button, 50);
// OneButton button(Swtich_Button, true);

// cLEDMatrix<MatrixWidth, MatrixHeight, MATRIX_TYPE> Matrixleds;
// cLEDText ScrollingMsg;

// const unsigned char TxtDemo[] = { EFFECT_SCROLL_LEFT "            LEFT SCROLL "
//                                   EFFECT_SCROLL_RIGHT "            LLORCS THGIR"
//                                   EFFECT_SCROLL_DOWN "            SCROLL DOWN             SCROLL DOWN            " EFFECT_FRAME_RATE "\x04" " SCROLL DOWN            " EFFECT_FRAME_RATE "\x00" " "
//                                   EFFECT_SCROLL_UP "             SCROLL UP               SCROLL UP             " EFFECT_FRAME_RATE "\x04" "  SCROLL UP             " EFFECT_FRAME_RATE "\x00" " "
//                                   EFFECT_CHAR_UP EFFECT_SCROLL_LEFT "            UP"
//                                   EFFECT_CHAR_RIGHT "  RIGHT"
//                                   EFFECT_CHAR_DOWN "  DOWN"
//                                   EFFECT_CHAR_LEFT "  LEFT"
//                                   EFFECT_HSV_CV "\x00\xff\xff\x40\xff\xff" EFFECT_CHAR_UP "           HSV_CV 00-40"
//                                   EFFECT_HSV_CH "\x00\xff\xff\x40\xff\xff" "    HSV_CH 00-40"
//                                   EFFECT_HSV_AV "\x00\xff\xff\x40\xff\xff" "    HSV_AV 00-40"
//                                   EFFECT_HSV_AH "\x00\xff\xff\xff\xff\xff" "    HSV_AH 00-FF"
//                                   "           " EFFECT_HSV "\x00\xff\xff" "R" EFFECT_HSV "\x20\xff\xff" "A" EFFECT_HSV "\x40\xff\xff" "I" EFFECT_HSV "\x60\xff\xff" "N" EFFECT_HSV "\xe0\xff\xff" "B" EFFECT_HSV "\xc0\xff\xff" "O"
//                                   EFFECT_HSV "\xa0\xff\xff" "W" EFFECT_HSV "\x80\xff\xff" "S " EFFECT_DELAY_FRAMES "\x00\x96" EFFECT_RGB "\xff\xff\xff" };


// TaskHandle_t refreshPanelHandle;
// void setup(){
//   Serial.begin(115200);

//   pinMode(Swtich_Button, INPUT);

//   FastLED.addLeds<CHIPSET, BoardPin, COLOR_ORDER>(leds, LED_NUM).setCorrection(TypicalSMD5050);
//   FastLED.setBrightness(64);
//   FastLED.clear(true);
//   // int** blocks = generatePlayingField(BoardWidth, BoardHeight);

//   ScrollingMsg.SetFont(MatriseFontData);
//   ScrollingMsg.Init(&Matrixleds, Matrixleds.Width(), ScrollingMsg.FontHeight() + 1, 0, 0);
//   ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
//   ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xff, 0x00, 0xff);

//   //generatePlayingField(10, BoardHeight);  
//   xTaskCreate(task_startup, "StartUp", 1028, (void *) 1, 1, NULL);
//   xTaskCreate(task_RefreshPanel, "RefreshPanel", 4096, (void *) 1, 1, &refreshPanelHandle);

//   vTaskSuspend(refreshPanelHandle);
//   FastLED.show();
// }

// void loop(){
// }


// void task_startup(void *param){
//   (void)param;
//   int durchlauf = 0;
//   int taskDelay = 10;
//   boolean ledstate = false;
//   int progressbar = 1;
//   for(;;){
//     bouncer.update();
//     if(doublePressed()){
//       vTaskResume(refreshPanelHandle);
//       vTaskDelete(NULL);
//     }

//     // if(durchlauf%50 == 0){
//     //   if(!ledstate){
//     //     drawRectangle(0, 0, progressbar, 1, CRGB(0,150,0), 25, true);
//     //   }else{
//     //     drawRectangle(0, 0, progressbar, 1, CRGB(0,0,0), 25, false);
//     //   }
//     //   ledstate = !ledstate;
//     // }

//     // if(durchlauf%((MAX_STARTUP_TIME/10)/BoardWidth) == 0){
//     //   progressbar++;
//     // }
//     // if(!ledstate){
//     //   togglePixel(0, 0, CRGB(0, 150, 0));
//     // }else{
//     //   togglePixel(0, 0, CRGB(0, 0, 0));
//     // }

//     ledstate = !ledstate;

//     if(durchlauf != 0 && durchlauf >= MAX_STARTUP_TIME/taskDelay){
//       drawRectangle(0, 0, progressbar, 1, CRGB(0,0,0), 0, false);

//       vTaskResume(refreshPanelHandle);

//       vTaskDelete(NULL);
//     }
//     durchlauf++;
//     vTaskDelay(taskDelay);
//   }
// }



// void task_RefreshPanel(void *param){
//   (void) param;

//   Serial.println("Task inited");
//   bool generated = false;
//   for(;;){
    
//     // drawRectangle(2, 2, 4, 4, CRGB(0, 255, 100), 50, true);
//     // vTaskDelay(50);
//     // drawRectangle(2,2, 4, 4, CRGB(0, 0, 0), 50, true);

//     //TODO try to understand int**
//     // if(!generated){
//     //   renderPlayingField(BoardWidth, BoardHeight, CRGB(0, 255, 100));
//     //   generated = true;
//     // }

//     // if(!generated){
//     //   printText("Hello");
//     // }

//     // generated = true;

//     if (ScrollingMsg.UpdateText() == -1)
//       ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
//     else
//       FastLED.show();
//     vTaskDelay(1000);
//   }
// }

// void togglePixel(int x, int y, CRGB color){

//   bool offset = false;
//   int result = 0;

//   if(y > 8){
//     offset = true;
//     y -= 8;
//   }

//   if(x%2 == 0)
//     result = x * 8 + y;
//   else 
//     result = x * 8 + (7 - y);


//   if(offset)
//     result += LED_NUM/2;

//   leds[result] = color;
//   FastLED.show();
// }

// void drawRectangle(int x, int y, int width, int height, CRGB color, int delay_time, bool reverse_delay){
//   if(delay_time <= 0)
//     delay_time = 1;
//   if(!reverse_delay)
//     delay_time = 0;

//   if(x < 0 || y < 0 || width <= 0 || height <= 0)
//     return;
  
//   for(int i = x; i < width + x; i++){
//     togglePixel(i, y, color);
//     delay(delay_time);
//   }
//   for(int i = y; i < y+height; i++){
//     togglePixel(width+x-1, i, color);
//     delay(delay_time);
//   }
//   if(height == 1 || width == 1)
//     return;

//   for(int i = x+width-1; i > x ; i--){
//     togglePixel(i, y+height-1, color);
//     delay(delay_time);
//   }
//   for(int i = y+height-1; i > y; i--){
//     togglePixel(x, i, color);
//     delay(delay_time);
//   }
// }


// int** generatePlayingField(int width, int height){
//   Serial.println("generating field...");
//   int gap = height/4;
//   int** block = 0;
//   block = new int*[width/2];

  
//   for(int i = 0; i < width/2; i++){
//     block[i] = new int[3];
//     int rand = 1 + (esp_random() % height/2);
//     block[i][0] = rand;
//     block[i][1] = rand+gap;
//     block[i][2] = (height-rand-gap);
//     Serial.println(i);
//   }
//   Serial.println("-------------");
//   Serial.println(sizeof(block[1]));
//   return block; 
// }

// void renderPlayingField(int width, int height, CRGB color){
//   int x_temp = 0;
//   int** block = generatePlayingField(width, height);

//   Serial.println("rendering field ...");
//   for(int i = 0; i < sizeof(block); i++){
//     drawRectangle(x_temp, 0, 1, block[i][0], color, 0, false);
//     drawRectangle(x_temp, block[i][1], 1, block[i][2], color, 0, false);
//     x_temp += 3;
//   }
// }

// long oldTime = 0;
// int pressed = 0;
// boolean doublePressed(){
//   if(bouncer.fell()){
//     Serial.println("pressed");
//     pressed++;
//     if(pressed >= 2){
//       if(millis() - oldTime <= 2000){
//         pressed = 0;
//         oldTime = millis();
//         togglePixel(0, 0, CRGB(0, 0, 0));
//         return true;
//       }else {
//         pressed = 0;
//         oldTime = millis();
//       }
//     }else {
//       oldTime = millis();
//     }
//   }
//   return false;
// }


// void printText(String message){
//   Serial.println("printing text...");
//   char msg_c[254];
//   unsigned char msg_uc[256] = {EFFECT_SCROLL_LEFT};                             // Prepare for an array of unsigned char

//   strncpy(msg_c, message.c_str(), 254);
  
//   std::copy(msg_c+2, msg_c + 256, msg_uc);                                      // Copy the char array to unsigned char, correctly converting
//   const unsigned char * TextMessage[] = { msg_uc };                              // Compose the message String into an LED Text Message
//   ScrollingMsg.UpdateText();
//   ScrollingMsg.SetText(msg_uc, 255);  
//   FastLED.show();
// }

#include "client_data.h"
#include <FastLED.h>
#include <ezTime.h>
#include <WiFi.h>

#include "LEDMatrix.h"
#include "LEDText.h"
#include "FontMatrise.h"

// Change the next 6 defines to match your matrix type and size

#define LED_PIN        A4
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B

#define MATRIX_WIDTH   32
#define MATRIX_HEIGHT  -8
#define MATRIX_TYPE    VERTICAL_ZIGZAG_MATRIX

//declare an instance of the cLEDMatrix class, used to declare and modify the LED data according to the matrix dimensions/layout/origin

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds2;

//declare the cLEDText class variable

cLEDText ScrollingMsg;
cLEDText ScrollingMsg2;

unsigned char TxtDemo[] = {"               @@@@@"
  EFFECT_DELAY_FRAMES "\x0f\xff"
};
unsigned char TxtDemo2[] = {"               @@"
  EFFECT_DELAY_FRAMES "\x0f\xff"
};
const void* val_ptr = memmem(TxtDemo, sizeof(TxtDemo), "@@@@@", 5);
const void* val_ptr2 = memmem(TxtDemo2, sizeof(TxtDemo2), "@@", 2);

Timezone myTZ;

const char* ntpServer = "0.pool.ntp.org";
const long offset = 3600;
const long dayLightOffset = 3600;

void setup() {
  
  Serial.begin(115200);
  const char* ssid = "Lol";
  const char* password = "Htlbeste";

  while (!Serial) { ; }

  //connect to WiFi and wait for ezTime to sync
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int connectCount = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    connectCount++;
    if(connectCount >= 10){
      ESP.restart();
    }
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  //create timezone variable and set location
  //offical timezone names can be found at: https://en.wikipedia.org/wiki/List_of_tz_database_time_zones
      //note - "US/Eastern", "US/Central", etc. don't work, the "notes" column of the table links to a working equivelent

  myTZ.setPosix("MESZ");

  Serial.println();
  Serial.println("The current time is " + myTZ.dateTime("g:i A T"));
  
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], leds.Size());
  FastLED.addLeds<CHIPSET, BoardPin2, COLOR_ORDER>(leds2[0], leds2.Size());
  FastLED.setBrightness(64);
  FastLED.clear(true);
  delay(100);
  
  ScrollingMsg.SetFont(MatriseFontData);
  ScrollingMsg2.SetFont(MatriseFontData);

  ScrollingMsg.Init(&leds, leds.Width(), ScrollingMsg.FontHeight() + 1, 0, 0);
  ScrollingMsg2.Init(&leds2, leds2.Width(), ScrollingMsg2.FontHeight() +1, 0, 0);

  ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
  ScrollingMsg2.SetText((unsigned char *)TxtDemo2, sizeof(TxtDemo2) - 1);

  ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xff, 0x00, 0xff);
  ScrollingMsg2.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xff, 0x00, 0xff);
}

void loop() {
  // get the time of day
  String currentTimeString = myTZ.dateTime("H:i");
  String currentTimeString2 = myTZ.dateTime("s");
  // copy the characters of the time String into the scrolltext
  memcpy8((void *)val_ptr, currentTimeString.c_str(), currentTimeString.length());
  memcpy8((void *)val_ptr2, currentTimeString2.c_str(), currentTimeString2.length());


  if (ScrollingMsg.UpdateText() == -1) {    
    ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
  }
  else {
    FastLED.show();
    delay(25);  
  }

  if (ScrollingMsg2.UpdateText() == -1) {    
    ScrollingMsg2.SetText((unsigned char *)TxtDemo2, sizeof(TxtDemo2) - 1);
  }
  else {
    FastLED.show();
    delay(25);  
  }
}