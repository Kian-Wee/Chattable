#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <FastLED.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>

#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>
#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>
#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>
#include <SoftwareSerial.h>

/* LedTable
 *
 * Written by: Klaas De Craemer, Ing. David Hrbaty
 * 
 * 
 * Main file with common methods and defines, such as button reading from Bluetooth controller
 * or setting pixels on the LED area
 */
#define FAST_LED_CHIPSET WS2812B

//Main LED pinout and pixels
#define  FIELD_WIDTH       10
#define  FIELD_HEIGHT      10
#define  ORIENTATION_HORIZONTAL //Rotation of table, uncomment to rotate field 90 degrees
#define FAST_LED_DATA_PIN  5

//Pinout and pixels of small led
//Left and Right score panels, unused
//#define mpinl 6
//#define mpinr 7
//#define SH 3
//#define SW 9

#define led1pin 8
#define led2pin 9
#define led3pin 10
#define led4pin 11
#define ORI_HORIZONTAL

#define  NUM_PIXELS    FIELD_WIDTH*FIELD_HEIGHT
//#define smallpixels    SW*SH

CRGB leds[NUM_PIXELS];
      CRGB led1[3];
      CRGB led2[3];
      CRGB led3[3];
      CRGB led4[3];
//CRGB leftled[smallpixels];
//CRGB rightled[smallpixels];

/* *** LED color table *** */
#define  GREEN  0x00FF00
#define  RED    0xFF00FF
#define  BLUE   0x0000FF
#define  YELLOW 0xFFFF00
#define  LBLUE  0x00FFFF
#define  PURPLE 0xFF00FF
#define  WHITE  0XFFFFFF
unsigned int colorLib[3] = {YELLOW, BLUE, WHITE};
/* *** Game commonly used defines ** */
#define  DIR_UP    1
#define  DIR_DOWN  2
#define  DIR_LEFT  3
#define  DIR_RIGHT 4

/* *** Bluetooth controller button defines and input method *** */
#define  BTN_NONE  0
#define  BTN_UP    1
#define  BTN_DOWN  2
#define  BTN_LEFT  3
#define  BTN_RIGHT  4
#define  BTN_START  5
#define  BTN_EXIT  6

uint8_t curControl = BTN_NONE;

#define p1L  43
#define p1M  45
#define p1R  47
#define p1S  49
#define p1LED  51

#define p2L  33
#define p2M  35
#define p2R  37
#define p2S  39
#define p2LED  41

#define p3L  48
#define p3M  46
#define p3R  44
#define p3S  42
#define p3LED  40// not working

#define p4L  34
#define p4M  36
#define p4R  41//38
#define p4S  32
#define p4LED  38

#define ptest 3

  int p1=0;
  int p2=0;
  int p3=0;
  int p4=0;

  // Params for width and height
const uint8_t kMatrixWidth = 10;
const uint8_t kMatrixHeight = 10;

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = true;
CRGB leds_plus_safety_pixel[ NUM_PIXELS + 1];
CRGB* const ledsmatrix( leds_plus_safety_pixel + 1);

int buttonStateL1 = 0;         // current state of the button
int lastButtonStateL1 = 0;     // previous state of the button
int buttonStateM1 = 0;         // current state of the button
int lastButtonStateM1 = 0;     // previous state of the button
int buttonStateR1 = 0;         // current state of the button
int lastButtonStateR1 = 0;     // previous state of the button
int buttonStateS1 = 0;         // current state of the button
int lastButtonStateS1 = 0;     // previous state of the button
int buttonStateE1 = 0;         // current state of the button
int lastButtonStateE1 = 0;     // previous state of the button

int buttonStateL2 = 0;         // current state of the button
int lastButtonStateL2 = 0;     // previous state of the button
int buttonStateM2 = 0;         // current state of the button
int lastButtonStateM2 = 0;     // previous state of the button
int buttonStateR2 = 0;         // current state of the button
int lastButtonStateR2 = 0;     // previous state of the button
int buttonStateS2 = 0;         // current state of the button
int lastButtonStateS2 = 0;     // previous state of the button
int buttonStateE2 = 0;         // current state of the button
int lastButtonStateE2 = 0;     // previous state of the button

int buttonStateL3 = 0;         // current state of the button
int lastButtonStateL3 = 0;     // previous state of the button
int buttonStateM3 = 0;         // current state of the button
int lastButtonStateM3 = 0;     // previous state of the button
int buttonStateR3 = 0;         // current state of the button
int lastButtonStateR3 = 0;     // previous state of the button
int buttonStateS3 = 0;         // current state of the button
int lastButtonStateS3 = 0;     // previous state of the button
int buttonStateE3 = 0;         // current state of the button
int lastButtonStateE3 = 0;     // previous state of the button

int buttonStateL4 = 0;         // current state of the button
int lastButtonStateL4 = 0;     // previous state of the button
int buttonStateM4 = 0;         // current state of the button
int lastButtonStateM4 = 0;     // previous state of the button
int buttonStateR4 = 0;         // current state of the button
int lastButtonStateR4 = 0;     // previous state of the button
int buttonStateS4 = 0;         // current state of the button
int lastButtonStateS4 = 0;     // previous state of the button
int buttonStateE4 = 0;         // current state of the button
int lastButtonStateE4 = 0;     // previous state of the button

int ingame=0;

void readInput(){

   int buttonpress =0;
   
   curControl = BTN_NONE;
        //Serial.println(buttonpress);

        buttonStateL1 = digitalRead(p1R);
        buttonStateM1 = digitalRead(p1M);
        buttonStateR1 = digitalRead(p1R);
        buttonStateS1 = digitalRead(p1S);
        buttonStateE1 = digitalRead(p1S);
        
        buttonStateL2 = digitalRead(p2R);
        buttonStateM2 = digitalRead(p2M);
        buttonStateR2 = digitalRead(p2R);
        buttonStateS2 = digitalRead(p2S);
        buttonStateE2 = digitalRead(p2S);
        
        buttonStateL3 = digitalRead(p4L);
        buttonStateM3 = digitalRead(p3M);
        buttonStateR3 = digitalRead(p3R);
        buttonStateS3 = digitalRead(p3S);
        buttonStateE3 = digitalRead(p3S);

        buttonStateL4 = digitalRead(p3L);
        buttonStateM4 = digitalRead(p4M);
        buttonStateR4 = digitalRead(p4R);
        buttonStateS4 = digitalRead(p4S);
        buttonStateE4 = digitalRead(p4S);

//---------------------------------------------
//PLAYER 1
      if (buttonStateL1 != lastButtonStateL1) {
    if (buttonStateL1 == LOW) {
            Serial.println("1BTN DOWN PRESSED");
            buttonpress=4;
    } else {}
    delay(50);
  }
  lastButtonStateL1 = buttonStateL1;

  if (buttonStateS1 != lastButtonStateS1) {
    if (buttonStateS1 == LOW) {
               Serial.println("BTN START PRESSED");
               buttonpress=5;
    } else {
      }
    delay(50);
  }
  lastButtonStateS1 = buttonStateS1;

  if (buttonStateE1 != lastButtonStateE1) {
    if (buttonStateE1 == HIGH) {
               Serial.println("BTN EXIT PRESSED");
               buttonpress=6;
    } else {
      }
    delay(50);
  }
  lastButtonStateE1 = buttonStateE1;

//PLAYER 2
 if (buttonStateL2 != lastButtonStateL2) {
    if (buttonStateL2 == LOW) {
             Serial.println("2BTN UP PRESSED");
             buttonpress=2;
    } else {}
    delay(50);
  }
  lastButtonStateL2 = buttonStateL2;

  if (buttonStateS2 != lastButtonStateS2) {
    if (buttonStateS2 == LOW) {
               Serial.println("2BTN START PRESSED");
               buttonpress=5;
    } else {
     // Serial.println("2BTN EXIT PRESSED");
      //buttonpress=6;
      }
    delay(50);
  }
  lastButtonStateS2 = buttonStateS2;

    if (buttonStateE2 != lastButtonStateE2) {
    if (buttonStateE2 == HIGH) {
               Serial.println("BTN EXIT PRESSED");
               buttonpress=6;
    } else {
      }
    delay(50);
  }
  lastButtonStateE2 = buttonStateE2;

//PLAYER 3
if (buttonStateL3 != lastButtonStateL3) {
    if (buttonStateL3 == LOW) {
        Serial.println("3BTN LEFT PRESSED");
        buttonpress=1;
    } else {}
    delay(50);
  }
  lastButtonStateL3 = buttonStateL3;

  if (buttonStateS3 != lastButtonStateS3) {
    if (buttonStateS3 == LOW) {
               Serial.println("BTN START PRESSED");
               buttonpress=5;
    } else {
      }
    delay(50);
  }
  lastButtonStateS3 = buttonStateS3;

    if (buttonStateE3 != lastButtonStateE3) {
    if (buttonStateE3 == HIGH) {
               Serial.println("BTN EXIT PRESSED");
               buttonpress=6;
    } else {
      }
    delay(50);
  }
  lastButtonStateE3 = buttonStateE3;

//PLAYER 4
 if (buttonStateL4 != lastButtonStateL4) {
    if (buttonStateL4 == LOW) {
             Serial.println("4BTN RIGHT PRESSED");
             buttonpress=3;
    } else {}
    delay(50);
  }
  lastButtonStateL4 = buttonStateL4;

  if (buttonStateS4 != lastButtonStateS4) {
    if (buttonStateS4 == LOW) {
               Serial.println("4BTN START PRESSED");
               buttonpress=5;
    } else {
      //Serial.println("4BTN EXIT PRESSED");
      //buttonpress=6;
      }
    delay(50);
  }
  lastButtonStateS4 = buttonStateS4;

  if (buttonStateE4 != lastButtonStateE4) {
    if (buttonStateE4 == HIGH) {
               Serial.println("BTN EXIT PRESSED");
               buttonpress=6;
    } else {
      }
    delay(50);
  }
  lastButtonStateE4 = buttonStateE4;

//------------------------
                
  /*
switch(ingame){
case 0:

case 1:
  //brickcontrol();
  Serial.println("case 1");
case 2:
  //snakecontrol();
  Serial.println("case 2");
}
*/
      switch(buttonpress){
        case 1:
          curControl = BTN_LEFT;
          Serial.println("Case Left");
          break;
        case 2:
          curControl = BTN_UP;
          Serial.println("Case Up");
          break;
        case 3:
          curControl = BTN_RIGHT;
          Serial.println("Case Right");
          break;
        case 4:
          curControl = BTN_DOWN;
          Serial.println("Case Down");
          break;
        case 5:
          curControl = BTN_START;
          Serial.println("Case Start");
          break;
        case 6:
          //players();
          curControl = BTN_EXIT;
          Serial.println("Case Exit");
          break;
      }
}

void players(){
      p1=0;
      p2=0;
      p3=0;
      p4=0;
  FastLED.clear();
  int et = millis() +5000;
  //player join light
  fill_solid(leds, 100, CRGB::Cyan); FastLED.show();
  Serial.println("Waiting for players");
  while(millis()<et){
      if(digitalRead(p1L)==LOW){
        setTablePixel(0, 0, RED); fill_solid(p1LED, 3, CRGB::Red); FastLED.show();
        p1=1;
        Serial.println("Player 1 Joined");
      }else if(digitalRead(p2L)==LOW){
        setTablePixel(0, 9, BLUE); fill_solid(p2LED, 3, CRGB::Blue); FastLED.show();
        p2=1;
        Serial.println("Player 2 Joined");
      }else if(digitalRead(p3L)==LOW){
        setTablePixel(9, 0, GREEN); fill_solid(p3LED, 3, CRGB::Green); FastLED.show();
        p3=1;
        Serial.println("Player 3 Joined");
      }else if(digitalRead(p4L)==LOW){
        setTablePixel(9, 9, YELLOW); fill_solid(p4LED, 3, CRGB::Yellow); FastLED.show();
        p4=1;
        Serial.println("Player 4 Joined");
      }
      Serial.println(millis());
  }
  //char playerstring[] = {p1,p2,p3,p4};
  //return playerstring;
  FastLED.clear();
}

int gamestart(){
  //players();
  if(p1==1 && p2==1 && p3==1 && p4==1){
    if(p1S==LOW && p2S==LOW && p3S==LOW && p4S==LOW){
      return 1;
    }
  }else if(p1==1){
    if(p1S==LOW){
      return 1;
    }
  }else if(p2==1){
    if(p2S==LOW){
      return 1;
    }
  }else if(p3==1){
    if(p3S==LOW){
      return 1;
    }
  }else if(p4==1){
    if(p4S==LOW){
      return 1;
    }
  }else if(p1==1&&p2==1){
    if(p1S==LOW&&p2S==LOW){
      return 1;
    }
  }else if(p1==1&&p3==1){
    if(p1S==LOW&&p3S==LOW){
      return 1;
    }
  }else if(p1==1&&p4==1){
    if(p1S==LOW&&p4S==LOW){
      return 1;
    }
  }else if(p2==1&&p3==1){
    if(p2S==LOW&&p3S==LOW){
      return 1;
    }
  }else if(p2==1&&p4==1){
    if(p2S==LOW&&p4S==LOW){
      return 1;
    }
  }else if(p3==1&&p4==1){
    if(p3S==LOW&&p4S==LOW){
      return 1;
    }
  }else if(p1==1&&p2==1&&p3==1){
    if(p1S==LOW&&p2S==LOW&&p3==LOW){
      return 1;
    }
  }else if(p1==1&&p2==1&&p4==1){
    if(p1S==LOW&&p2S==LOW&&p4==LOW){
      return 1;
    }
   }else if(p2==1&&p3==1&&p4==1){
    if(p2S==LOW&&p3==LOW&&p4S==LOW){
      return 1;
    }
}
return 0;
}

void initPixels(){
  FastLED.addLeds<FAST_LED_CHIPSET, FAST_LED_DATA_PIN, GRB>(leds, NUM_PIXELS).setCorrection(TypicalSMD5050);
  //FastLED.addLeds<FAST_LED_CHIPSET, mpinl, BRG>(leftled, smallpixels).setCorrection(TypicalSMD5050);
  //FastLED.addLeds<FAST_LED_CHIPSET, mpinr, BRG>(rightled, smallpixels).setCorrection(TypicalSMD5050);
  //extern struct CRGB led1[3];
  //added in
  FastLED.setBrightness(255);

      
      FastLED.addLeds<FAST_LED_CHIPSET, p1LED, GRB>(led1, 3).setCorrection(TypicalSMD5050);
      FastLED.addLeds<FAST_LED_CHIPSET, p2LED, GRB>(led2, 3).setCorrection(TypicalSMD5050);
      FastLED.addLeds<FAST_LED_CHIPSET, p3LED, GRB>(led3, 3).setCorrection(TypicalSMD5050);
      FastLED.addLeds<FAST_LED_CHIPSET, p4LED, GRB>(led4, 3).setCorrection(TypicalSMD5050);

      fill_solid(led1,3,CRGB::White);
      fill_solid(led2,3,CRGB::White);
      fill_solid(led3,3,CRGB::White);
      fill_solid(led4,3,CRGB::White);
      FastLED.show();
}

void clearcontrollerled(){
          for(int dot = 0; dot < 3; dot++) { 
            led1[dot] = CRGB::Black;
            delay(30);
        }
                  for(int dot = 0; dot < 3; dot++) { 
            led2[dot] = CRGB::Black;
            delay(30);
        }
                  for(int dot = 0; dot < 3; dot++) { 
            led3[dot] = CRGB::Black;
            delay(30);
        }
                  for(int dot = 0; dot < 3; dot++) { 
            led4[dot] = CRGB::Black;
            delay(30);
        }
        FastLED.show();
}


void setPixel(int n, int color){
  leds[n] = CRGB(color);
}

void setPixelRGB(int n, int r,int g, int b){
  leds[n] = CRGB(r,g,b);
}

void setDelay(int duration) {
  FastLED.delay(duration);
}

int getPixel(int n){
  return (leds[n].r << 16) + (leds[n].g << 8) + leds[n].b;  
}
/*
int getsmallPixel(int m, int n){
  return (leftled[n].r << 16) + (leftled[n].g << 8) + leftled[n].b;
  return (rightled[n].r << 16) + (rightled[n].g << 8) + rightled[n].b;    
}
*/
void showPixels(){
  FastLED.show();
}




void setTablePixel(int x, int y, int color){
  #ifdef ORIENTATION_HORIZONTAL
  setPixel(y%2 ? y*FIELD_WIDTH + x : y*FIELD_WIDTH + ((FIELD_HEIGHT-1)-x),color);
    #ifdef USE_CONSOLE_OUTPUT
      setTablePixelConsole(y,x,color);
    #endif
  #else
  setPixel(x%2 ? x*FIELD_WIDTH + ((FIELD_HEIGHT-1)-y) : x*FIELD_WIDTH + y,color);
    #ifdef USE_CONSOLE_OUTPUT
      setTablePixelConsole(x,y,color);
    #endif
  #endif
}
/*
void setsmallPixel(int x, int y, int color){
  #ifdef ORI_HORI
  setPixel(y%2 ? y*SW + x : y*SW + ((SH-1)-x),color);
    #ifdef USE_CONSOLE_OUTPUT
      setTablePixelConsole(y,x,color);
    #endif
  #else
  setPixel(x%2 ? x*SW + ((SH-1)-y) : x*SW + y,color);
    #ifdef USE_CONSOLE_OUTPUT
      setTablePixelConsole(x,y,color);
    #endif
  #endif
}
*/



void setTablePixelRGB(int x, int y, int r,int g, int b){
  #ifdef ORIENTATION_HORIZONTAL
  setPixelRGB(y%2 ? y*FIELD_WIDTH + x : y*FIELD_WIDTH + ((FIELD_HEIGHT-1)-x),r,g,b);
    #ifdef USE_CONSOLE_OUTPUT
      setTablePixelConsole(y,x,color);
    #endif
  #else
  setPixelRGB(x%2 ? x*FIELD_WIDTH + ((FIELD_HEIGHT-1)-y) : x*FIELD_WIDTH + y,r,g,b);
    #ifdef USE_CONSOLE_OUTPUT
      setTablePixelConsole(x,y,color);
    #endif
  #endif
}
/*
void setsmallPixelRGB(int x, int y, int r,int g, int b){
  #ifdef ORI_HORI
  setPixelRGB(y%2 ? y*SW + x : y*SW + ((SH-1)-x),r,g,b);
    #ifdef USE_CONSOLE_OUTPUT
      setTablePixelConsole(y,x,color);
    #endif
  #else
  setPixelRGB(x%2 ? x*SW + ((SH-1)-y) : x*SW + y,r,g,b);
    #ifdef USE_CONSOLE_OUTPUT
      setTablePixelConsole(x,y,color);
    #endif
  #endif
}
*/



void clearTablePixels(){
  for (int n=0; n<FIELD_WIDTH*FIELD_HEIGHT; n++){
    setPixel(n,0);
  }
}


/*
void clearsmallPixels(){
  for (int n=0; n<SW*SH; n++){
    setPixel(n,0);
  }
}
*/


/* *** text helper methods *** */
#include "font.h"
uint8_t charBuffer[8][8];

void printText(char* text, unsigned int textLength, int xoffset, int yoffset, int color){
  uint8_t curLetterWidth = 0;
  int curX = xoffset;
  clearTablePixels();
  
  //Loop over all the letters in the string
  for (int i=0; i<textLength; i++){
    //Determine width of current letter and load its pixels in a buffer
    curLetterWidth = loadCharInBuffer(text[i]);
    //Loop until width of letter is reached
    for (int lx=0; lx<curLetterWidth; lx++){
      //Now copy column per column to field (as long as within the field
      if (curX>=FIELD_WIDTH){//If we are to far to the right, stop loop entirely
        break;
      } else if (curX>=0){//Draw pixels as soon as we are "inside" the drawing area
        for (int ly=0; ly<8; ly++){//Finally copy column
          setTablePixel(curX,yoffset+ly,charBuffer[lx][ly]*color);
        }
      }
      curX++;
    }
  }
  
  showPixels();
}
/*
void printsmallText(char* text, unsigned int textLength, int xoffset, int yoffset, int color){
  uint8_t curLetterWidth = 0;
  int curX = xoffset;
  clearsmallPixels();
  
  //Loop over all the letters in the string
  for (int i=0; i<textLength; i++){
    //Determine width of current letter and load its pixels in a buffer
    curLetterWidth = loadCharInBuffer(text[i]);
    //Loop until width of letter is reached
    for (int lx=0; lx<curLetterWidth; lx++){
      //Now copy column per column to field (as long as within the field
      if (curX>=SW){//If we are to far to the right, stop loop entirely
        break;
      } else if (curX>=0){//Draw pixels as soon as we are "inside" the drawing area
        for (int ly=0; ly<8; ly++){//Finally copy column
          setsmallPixel(curX,yoffset+ly,charBuffer[lx][ly]*color);
        }
      }
      curX++;
    }
  }
  
  showPixels();
}
*/



//Load char in buffer and return width in pixels
uint8_t loadCharInBuffer(char letter){
  uint8_t* tmpCharPix;
  uint8_t tmpCharWidth;
  
  int letterIdx = (letter-32)*8;
  
  int x=0; int y=0;
  for (int idx=letterIdx; idx<letterIdx+8; idx++){
    for (int x=0; x<8; x++){
      charBuffer[x][y] = ((font[idx]) & (1<<(7-x)))>0;
    }
    y++;
  }
  
  tmpCharWidth = 8;
  return tmpCharWidth;
}


/* *********************************** */

void fadeOut(){
  //Select random fadeout animation
  int selection = random(3);
  
  switch(selection){
    case 0:
    case 1:
    {
      //Fade out by dimming all pixels
      for (int i=0; i<100; i++){
        dimLeds(0.97);
        showPixels();
        delay(10);
      }
      break;
    }
    case 2:
    {
      //Fade out by swiping from left to right with ruler
      const int ColumnDelay = 10;
      int curColumn = 0;
      for (int i=0; i<FIELD_WIDTH*ColumnDelay; i++){
        dimLeds(0.97);
        if (i%ColumnDelay==0){
          //Draw vertical line
          for (int y=0;y<FIELD_HEIGHT;y++){
            setTablePixel(curColumn, y, GREEN);
          }
          curColumn++;
        }
        showPixels();
        delay(5);
      }
      //Sweep complete, keep dimming leds for short time
      for (int i=0; i<100; i++){
        dimLeds(0.9);
        showPixels();
        delay(5);
      }
      break;
    }
  }
}

void dimLeds(float factor){
  //Reduce brightness of all LEDs, typical factor is 0.97
  for (int n=0; n<(FIELD_WIDTH*FIELD_HEIGHT); n++){
    int curColor = getPixel(n);
    //Derive the tree colors
    int r = ((curColor & 0xFF0000)>>16);
    int g = ((curColor & 0x00FF00)>>8);
    int b = (curColor & 0x0000FF);
    //Reduce brightness
    r = r*factor;
    g = g*factor;
    b = b*factor;
    //Pack into single variable again
    curColor = (r<<16) + (g<<8) + b;
    //Set led again
    setPixel(n,curColor);
  }
}

void testMatrix() {
    setTablePixel(0, 0, WHITE);
    showPixels();
    delay(2000);
    setTablePixel(0, 9, WHITE);
    showPixels();
    delay(2000);
    setTablePixel(9, 0, WHITE);
    showPixels();
    delay(2000);
    setTablePixel(9, 9, WHITE);
    showPixels();
    delay(2000);
}

void setup(){
  Serial.begin(115200);
  //Wait for serial port to connect
  //bluetooth.begin(BLUETOOTH_SPEED);
  //Initialise display
    Serial.println("Running Main loop");
  pinMode(p1L, INPUT_PULLUP);
  pinMode(p1M, INPUT_PULLUP);
  pinMode(p1R, INPUT_PULLUP);
  pinMode(p1S, INPUT_PULLUP);
  //pinMode(p1LED, OUTPUT);
  pinMode(p2L, INPUT_PULLUP);
  pinMode(p2M, INPUT_PULLUP);
  pinMode(p2R, INPUT_PULLUP);
  pinMode(p2S, INPUT_PULLUP);
  //pinMode(p2LED, OUTPUT);
  pinMode(p3L, INPUT_PULLUP);
  pinMode(p3M, INPUT_PULLUP);
  pinMode(p3R, INPUT_PULLUP);
  pinMode(p3S, INPUT_PULLUP);
  //pinMode(p3LED, OUTPUT);
  pinMode(p4L, INPUT_PULLUP);
  pinMode(p4M, INPUT_PULLUP);
  pinMode(p4R, INPUT_PULLUP);
  pinMode(p4S, INPUT_PULLUP);
  //pinMode(p4LED, OUTPUT);
  pinMode(ptest, INPUT_PULLUP);
  
  initPixels();
  showPixels();

  //testMatrix();

  //Init random number generator
  randomSeed(millis());
  //players();
  mainLoop();
}

void loop(){
}
/*
void menucontrol(){

//---------------------------------------------
//PLAYER 1
      if (buttonStateL1 != lastButtonStateL1) {
    if (buttonStateL1 == LOW) {
        Serial.println("BTN LEFT PRESSED");
        buttonpress=1;
    } else {}
    delay(50);
  }
  lastButtonStateL1 = buttonStateL1;

  if (buttonStateM1 != lastButtonStateM1) {
    if (buttonStateM1 == LOW) {
             Serial.println("BTN UP PRESSED");
             buttonpress=2;
    } else {}
    delay(50);
  }
  lastButtonStateM1 = buttonStateM1;
  
  if (buttonStateR1 != lastButtonStateR1) {
    if (buttonStateR1 == LOW) {
             Serial.println("BTN RIGHT PRESSED");
             buttonpress=3;
    } else {}
    delay(50);
  }
  lastButtonStateR1 = buttonStateR1;

  if (buttonStateS1 != lastButtonStateS1) {
    if (buttonStateS1 == LOW) {
               Serial.println("BTN START PRESSED");
               buttonpress=5;
    } else {
      }
    delay(50);
  }
  lastButtonStateS1 = buttonStateS1;

  if (buttonStateE1 != lastButtonStateE1) {
    if (buttonStateE1 == HIGH) {
               Serial.println("BTN EXIT PRESSED");
               buttonpress=6;
    } else {
      }
    delay(50);
  }
  lastButtonStateE1 = buttonStateE1;

//PLAYER 2
 if (buttonStateL2 != lastButtonStateL2) {
    if (buttonStateL2 == LOW) {
        Serial.println("2BTN LEFT PRESSED");
        buttonpress=1;
    } else {}
    delay(50);
  }
  lastButtonStateL2 = buttonStateL2;

 if (buttonStateM2 != lastButtonStateM2) {
    if (buttonStateM2 == LOW) {
               Serial.println("2BTN DOWN PRESSED");
               buttonpress=4;
    } else {}
    delay(50);
  }
  lastButtonStateM2 = buttonStateM2;
  
  if (buttonStateR2 != lastButtonStateR2) {
    if (buttonStateR2 == LOW) {
             Serial.println("2BTN RIGHT PRESSED");
             buttonpress=3;
    } else {}
    delay(50);
  }
  lastButtonStateR2 = buttonStateR2;

  if (buttonStateS2 != lastButtonStateS2) {
    if (buttonStateS2 == LOW) {
               Serial.println("2BTN START PRESSED");
               buttonpress=5;
    } else {
     // Serial.println("2BTN EXIT PRESSED");
      //buttonpress=6;
      }
    delay(50);
  }
  lastButtonStateS2 = buttonStateS2;

    if (buttonStateE2 != lastButtonStateE2) {
    if (buttonStateE2 == HIGH) {
               Serial.println("BTN EXIT PRESSED");
               buttonpress=6;
    } else {
      }
    delay(50);
  }
  lastButtonStateE2 = buttonStateE2;

//PLAYER 3
if (buttonStateL3 != lastButtonStateL3) {
    if (buttonStateL3 == LOW) {
        Serial.println("3BTN LEFT PRESSED");
        buttonpress=1;
    } else {}
    delay(50);
  }
  lastButtonStateL3 = buttonStateL3;

  if (buttonStateM3 != lastButtonStateM3) {
    if (buttonStateM3 == LOW) {
             Serial.println("3BTN UP PRESSED");
             buttonpress=2;
    } else {}
    delay(50);
  }
  lastButtonStateM3 = buttonStateM3;
  
  if (buttonStateR3 != lastButtonStateR3) {
    if (buttonStateR3 == LOW) {
             Serial.println("3BTN RIGHT PRESSED");
             buttonpress=3;
    } else {}
    delay(50);
  }
  lastButtonStateR3 = buttonStateR3;

  if (buttonStateS3 != lastButtonStateS3) {
    if (buttonStateS3 == LOW) {
               Serial.println("BTN START PRESSED");
               buttonpress=5;
    } else {
      //Serial.println("BTN EXIT PRESSED");
      //buttonpress=6;
      }
    delay(50);
  }
  lastButtonStateS3 = buttonStateS3;

    if (buttonStateE3 != lastButtonStateE3) {
    if (buttonStateE3 == HIGH) {
               Serial.println("BTN EXIT PRESSED");
               buttonpress=6;
    } else {
      }
    delay(50);
  }
  lastButtonStateE3 = buttonStateE3;

//PLAYER 4
 if (buttonStateL4 != lastButtonStateL4) {
    if (buttonStateL4 == LOW) {
        Serial.println("4BTN LEFT PRESSED");
        buttonpress=1;
    } else {}
    delay(50);
  }
  lastButtonStateL4 = buttonStateL4;

 if (buttonStateM4 != lastButtonStateM4) {
    if (buttonStateM4 == LOW) {
               Serial.println("4BTN DOWN PRESSED");
               buttonpress=4;
    } else {}
    delay(50);
  }
  lastButtonStateM4 = buttonStateM4;
  
  if (buttonStateR4 != lastButtonStateR4) {
    if (buttonStateR4 == LOW) {
             Serial.println("4BTN RIGHT PRESSED");
             buttonpress=3;
    } else {}
    delay(50);
  }
  lastButtonStateR4 = buttonStateR4;

  if (buttonStateS4 != lastButtonStateS4) {
    if (buttonStateS4 == LOW) {
               Serial.println("4BTN START PRESSED");
               buttonpress=5;
    } else {
      //Serial.println("4BTN EXIT PRESSED");
      //buttonpress=6;
      }
    delay(50);
  }
  lastButtonStateS4 = buttonStateS4;

  if (buttonStateE4 != lastButtonStateE4) {
    if (buttonStateE4 == HIGH) {
               Serial.println("BTN EXIT PRESSED");
               buttonpress=6;
    } else {
      }
    delay(50);
  }
  lastButtonStateE4 = buttonStateE4;

//------------------------
}


void snakecontrol(){
  //PLAYER 1
  if (buttonStateL1 != lastButtonStateL1) {
    if (buttonStateL1 == LOW) {
        Serial.println("BTN LEFT PRESSED");
        buttonpress=1;
    } else {}
    delay(50);
  }
  lastButtonStateL1 = buttonStateL1;
  Serial.print("Button state L1: ");
  Serial.println(buttonStateL1);
  Serial.print("Last Button state L1: ");
  Serial.println(lastButtonStateL1);

//PLAYER 2
 if (buttonStateM2 != lastButtonStateM2) {
    if (buttonStateM2 == LOW) {
               Serial.println("2BTN DOWN PRESSED");
               buttonpress=4;
    } else {}
    delay(50);
  }
  lastButtonStateM2 = buttonStateM2;

//PLAYER 3
  if (buttonStateM3 != lastButtonStateM3) {
    if (buttonStateM3 == LOW) {
             Serial.println("3BTN UP PRESSED");
             buttonpress=2;
    } else {}
    delay(50);
  }
  lastButtonStateM3 = buttonStateM3;
  
//PLAYER 4
  if (buttonStateR4 != lastButtonStateR4) {
    if (buttonStateR4 == LOW) {
             Serial.println("4BTN RIGHT PRESSED");
             buttonpress=3;
    } else {}
    delay(50);
  }
  lastButtonStateR4 = buttonStateR4;

//START AND STOP

  if (buttonStateS1 != lastButtonStateS1) {
    if (buttonStateS1 == LOW) {
               Serial.println("BTN START PRESSED");
               buttonpress=5;
    } else {
      Serial.println("BTN EXIT PRESSED");
      buttonpress=6;}
    delay(50);
  }
  lastButtonStateS1 = buttonStateS1;

  if (buttonStateS2 != lastButtonStateS2) {
    if (buttonStateS2 == LOW) {
               Serial.println("2BTN START PRESSED");
               buttonpress=5;
    } else {
      Serial.println("2BTN EXIT PRESSED");
      buttonpress=6;}
    delay(50);
  }
  lastButtonStateS2 = buttonStateS2;
  
    if (buttonStateS3 != lastButtonStateS3) {
    if (buttonStateS3 == LOW) {
               Serial.println("3BTN START PRESSED");
               buttonpress=5;
    } else {
      Serial.println("3BTN EXIT PRESSED");
      buttonpress=6;}
    delay(50);
  }
  lastButtonStateS3 = buttonStateS3;
  
  if (buttonStateS4 != lastButtonStateS4) {
    if (buttonStateS4 == LOW) {
               Serial.println("4BTN START PRESSED");
               buttonpress=5;
    } else {
      Serial.println("4BTN EXIT PRESSED");
      buttonpress=6;}
    delay(50);
  }
  lastButtonStateS4 = buttonStateS4;
}

void brickcontrol(){
  
}
*/



uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  
  if( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }

  if( kMatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }
  
  return i;
}

uint16_t XYsafe( uint8_t x, uint8_t y)
{
  if( x >= kMatrixWidth) return -1;
  if( y >= kMatrixHeight) return -1;
  return XY(x,y);
}

boolean matrixRunning = true;
/*
void runmatrix(){
  matrixRunning = true;
  while (matrixRunning){
    rgbmatrix();
  }
  fadeOut();
}
*/

void runmatrix(){
  readInput();
  if (curControl != BTN_EXIT){
    rgbmatrix();
  }
  fadeOut();
}


void rgbmatrix(){
//  for(int x = 0; x < 255; x ++){
    uint32_t ms = millis();
    int32_t yHueDelta32 = ((int32_t)cos16( ms * (27/1) ) * (350 / kMatrixWidth));
    int32_t xHueDelta32 = ((int32_t)cos16( ms * (39/1) ) * (310 / kMatrixHeight));
    DrawOneFrame( ms / 65536, yHueDelta32 / 32768, xHueDelta32 / 32768);
    if( ms < 5000 ) {
      FastLED.setBrightness( scale8( 255, (ms * 256) / 5000));
    } else {
      FastLED.setBrightness(255);
    }
    FastLED.show();
    /*
    //Read buttons
    readInput();
    if (curControl == BTN_START){
      Serial.println("START");
      matrixRunning = false;
      break;
    }
    delayMicroseconds(50);
    */
  }

void DrawOneFrame( byte startHue8, int8_t yHueDelta8, int8_t xHueDelta8)
{
  byte lineStartHue = startHue8;
  for( byte y = 0; y < kMatrixHeight; y++) {
    lineStartHue += yHueDelta8;
    byte pixelHue = lineStartHue;      
    for( byte x = 0; x < kMatrixWidth; x++) {
      pixelHue += xHueDelta8;
      ledsmatrix[XY(x, y)]  = CHSV( pixelHue, 255, 255);
    }
  }
}
