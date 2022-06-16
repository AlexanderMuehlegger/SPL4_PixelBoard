#include <client_data.h>

CRGB leds_plus_safety_pixel[LED_NUM + 1];
CRGB *const leds(leds_plus_safety_pixel + 1);

bool startup_completed = false;
Bounce bouncer = Bounce(Swtich_Button, 50);
OneButton button(Swtich_Button, true);

TaskHandle_t refreshPanelHandle;
void setup(){
  Serial.begin(115200);
  // Serial.println("NUM LEDS: ");
  // Serial.print(LED_NUM + "\n");
  pinMode(Swtich_Button, INPUT);
  FastLED.addLeds<CHIPSET, BoardPin, COLOR_ORDER>(leds, LED_NUM).setCorrection(TypicalSMD5050);

  FastLED.clear();
  FastLED.show();
  // int** blocks = generatePlayingField(BoardWidth, BoardHeight);

  //generatePlayingField(10, BoardHeight);  
  xTaskCreate(task_startup, "StartUp", 1028, (void *) 1, 1, NULL);
  xTaskCreate(task_RefreshPanel, "RefreshPanel", 4096, (void *) 1, 1, &refreshPanelHandle);

  vTaskSuspend(refreshPanelHandle);
}

void loop(){
}


void task_startup(void *param){
  (void)param;
  int durchlauf = 0;
  int taskDelay = 10;
  boolean ledstate = false;
  int progressbar = 1;
  for(;;){
    bouncer.update();
    if(doublePressed()){
      vTaskResume(refreshPanelHandle);
      vTaskDelete(NULL);
    }

    if(durchlauf%50 == 0){
      if(!ledstate){
        drawRectangle(0, 0, progressbar, 1, CRGB(0,150,0), 25, true);
      }else{
        drawRectangle(0, 0, progressbar, 1, CRGB(0,0,0), 25, false);
      }
      ledstate = !ledstate;
    }

    if(durchlauf%((MAX_STARTUP_TIME/10)/BoardWidth) == 0){
      progressbar++;
    }

    if(durchlauf != 0 && durchlauf >= MAX_STARTUP_TIME/taskDelay){
      drawRectangle(0, 0, progressbar, 1, CRGB(0,0,0), 0, false);

      vTaskResume(refreshPanelHandle);

      vTaskDelete(NULL);
    }
    durchlauf++;
    vTaskDelay(taskDelay);
  }
}



void task_RefreshPanel(void *param){
  (void) param;

  Serial.println("Task inited");
  
  for(;;){
    
    drawRectangle(2, 2, 4, 4, CRGB(0, 255, 100), 50, true);
    vTaskDelay(50);
    drawRectangle(2,2, 4, 4, CRGB(0, 0, 0), 50, true);
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

void drawRectangle(int x, int y, int width, int height, CRGB color, int delay_time, bool reverse_delay){
  if(delay_time <= 0)
    delay_time = 1;
  if(!reverse_delay)
    delay_time = 0;

  if(x < 0 || y < 0 || width <= 0 || height <= 0)
    return;
  
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
}


int** generatePlayingField(int width, int height){
  int gap = height/4;
  int** block = 0;
  block = new int*[width/2];

  for(int i = 0; width/2; i++){
    block[i] = new int[height];
    int rand = 0 + (esp_random() % height/2);
    block[i][0] = rand;
    block[i][1] = rand+gap;
    block[i][2] = (height-rand-gap);
  }
  return block;
}

void renderPlayingField(int width, int height, int** block, CRGB color){
  int x_temp = 0;
  for(int i = 0; i < sizeof(block); i++){
    drawRectangle(x_temp, 0, 1, block[i][0], color, 0, false);
    drawRectangle(x_temp, block[i][1], 1, block[i][2], color, 0, false);
    x_temp += 2;
  }
}

long oldTime = 0;
int pressed = 0;
boolean doublePressed(){
  if(bouncer.fell()){
    pressed++;
    if(pressed >= 2){
      if(millis() - oldTime <= 2000){
        pressed = 0;
        oldTime = millis();
        togglePixel(0, 0, CRGB(0, 0, 0));
        return true;
      }else {
        pressed = 0;
        oldTime = millis();
      }
    }else {
      oldTime = millis();
    }
  }
  return false;
}
