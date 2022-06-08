#include <client_data.h>

CRGB leds_plus_safety_pixel[LED_NUM + 1];
CRGB *const leds(leds_plus_safety_pixel + 1);

void setup(){
  Serial.begin(115200);
  // Serial.println("NUM LEDS: ");
  // Serial.print(LED_NUM + "\n");
  
  FastLED.addLeds<CHIPSET, BoardPin, COLOR_ORDER>(leds, LED_NUM).setCorrection(TypicalSMD5050);

  FastLED.clear();
  FastLED.show();
  int blocks[][3] = generatePlayingField();

  generatePlayingField(10, BoardHeight);  
  // xTaskCreate(task_RefreshPanel, "RefreshPanel", 4096, (void *) 1, 1, NULL);
}

void loop(){}

int durchlauf = 0;
void task_RefreshPanel(void *param){
  (void) param;

  Serial.println("Task inited");
  
  for(;;){
    drawRectangle(2, 2, 4, 4, CRGB(0, 255, 100), 50);
    vTaskDelay(50);
    drawRectangle(2,2, 4, 4, CRGB(0, 0, 0), 50);
  }
}

void togglePixel(int x, int y, CRGB color){

  bool offset = false;
  int result = 0;

  if(y > 8){
    offset = true;
    y -= 8;
  }

  if(x%2 == 0)
    result = x * 8 + y;
  else 
    result = x * 8 + (7 - y);


  if(offset)
    result += LED_NUM/2;

  leds[result] = color;
  FastLED.show();
}

void drawRectangle(int x, int y, int width, int height, CRGB color, int delay_time){
  if(delay_time <= 0)
    delay_time = 1;

  Serial.println("welcome");
  if(x < 0 || y < 0 || width <= 0 || height <= 0)
    return;

  Serial.println("hello World");
  
  for(int i = x; i < width + x; i++){
    togglePixel(i, y, color);
    delay(delay_time);
  }
  for(int i = y; i < y+height; i++){
    togglePixel(width+x-1, i, color);
    delay(delay_time);
  }
  if(height == 1 || width == 1)
    return;

  for(int i = x+width-1; i > x ; i--){
    togglePixel(i, y+height-1, color);
    delay(delay_time);
  }
  for(int i = y+height-1; i > y; i--){
    togglePixel(x, i, color);
    delay(delay_time);
  }
  Serial.println("finished");
}


int** generatePlayingField(int width, int height){
  int gap = height/4;
  int block[width/2][3];

  for(int i = 0; width/2; i++){
    int rand = 0 + (esp_random() % height/2);
    block[i][0] = rand;
    block[i][1] = rand+gap;
    block[i][2] = (height-rand-gap);
  }
  return block;
}

void renderPlayingField(int width, int height, int block[][3], CRGB color){
  int x_temp = 0;
  for(int i = 0; i < sizeof(block); i++){
    drawRectangle(x_temp, 0, 1, block[i][0], color, 0);
    drawRectangle(x_temp, block[i][1], 1, block[i][2], color, 0);
    x_temp += 2;
  }
}