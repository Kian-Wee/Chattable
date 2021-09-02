/* LedTable
 *
 * Written by: Klaas De Craemer, Ing. David Hrbaty
 * 
 * Menu system for the LED table
 */
#define MINSELECTION  1
#define MAXSELECTION  9
unsigned int curSelection = MINSELECTION;

int startled=0;
      //CRGB led1[3];
      //CRGB led2[3];
      //CRGB led3[3];
      //CRGB led4[3];
      
//default 140
#define TEXTSPEED  150

void mainLoop(void){
  char* curSelectionText;
  int curSelectionTextLength;
  unsigned long prevUpdateTime = 0;
/*
  if(startled=0){
      FastLED.addLeds<FAST_LED_CHIPSET, p1LED, GRB>(led1, 3).setCorrection(TypicalSMD5050);
      FastLED.addLeds<FAST_LED_CHIPSET, p2LED, GRB>(led2, 3).setCorrection(TypicalSMD5050);
      FastLED.addLeds<FAST_LED_CHIPSET, p3LED, GRB>(led3, 3).setCorrection(TypicalSMD5050);
      FastLED.addLeds<FAST_LED_CHIPSET, p4LED, GRB>(led4, 3).setCorrection(TypicalSMD5050);
      /*
      fill_solid(led1,3,CRGB::White);
      fill_solid(led2,3,CRGB::White);
      fill_solid(led3,3,CRGB::White);
      fill_solid(led4,3,CRGB::White);
      
      led1[1] = CRGB::Red;
      led2[1] = CRGB::Red;
      led3[1] = CRGB::Red;
      led4[1] = CRGB::Red;
      FastLED.show();
      startled=1;
      Serial.println("Controller LED INIT");
  }
  **/
  while(true){
    //Show menu system and wait for input
    clearTablePixels();
    ingame=0;
    switch (curSelection){
      case 1:
        Serial.println("Chattable");
        curSelectionText = "ChaTTable";
        curSelectionTextLength = 9;
        //Serial.println("Tetris Select");
        //curSelectionText = "6 Tetris";
        //curSelectionTextLength = 8;
        break;
      case 2:
        Serial.println("Rainbow Select");
        curSelectionText = "1 Rainbow";
        curSelectionTextLength = 9;
        break;
      case 3:
        Serial.println("Animation Select");
        curSelectionText = "2 Animation";
        curSelectionTextLength = 11;
        break;    
      case 4:
        Serial.println("Stars Select");
        curSelectionText = "3 Stars";
        curSelectionTextLength = 7;
        break;  
      case 5:
        Serial.println("VU Select");
        curSelectionText = "4 Vu Meter";
        curSelectionTextLength = 10;
        break;    
      case 6:
        Serial.println("Dice Select");
        curSelectionText = "5 Dice"; 
        curSelectionTextLength = 6;
        break;                
      case 7:
        Serial.println("Snake Select");
        curSelectionText = "7 Snake";
        curSelectionTextLength = 7;
        break;
      case 8:
        Serial.println("Pong Select");
        curSelectionText = "8 Pong";
        curSelectionTextLength = 6;
        break;       
      case 9:
        Serial.println("Bricks Select");
        curSelectionText = "9 Bricks";
        curSelectionTextLength = 8;
        break;
    }
    
    boolean selectionChanged = false;
    boolean runSelection = false;
    //Scroll current selection text from right to left;
    for (int x=FIELD_WIDTH; x>-(curSelectionTextLength*8); x--){
      printText(curSelectionText, curSelectionTextLength, x, (FIELD_HEIGHT-8)/2, YELLOW);
      //Read buttons
      unsigned long curTime;
      do{
        readInput();
        if (curControl != BTN_NONE){
          if (curControl == BTN_LEFT){
            curSelection--;
            selectionChanged = true;
            Serial.println("Selection moved left");
          } else if (curControl == BTN_RIGHT){
            curSelection++;
            selectionChanged = true;
            Serial.println("Selection moved right");
          } else if (curControl == BTN_START){
            runSelection = true;
            Serial.println("Selection selected start");
          }
          
          checkSelectionRange();
        }
        curTime = millis();
      } while (((curTime - prevUpdateTime) < TEXTSPEED) && (curControl == BTN_NONE));//Once enough time  has passed, proceed
      prevUpdateTime = curTime;
      
      if (selectionChanged || runSelection)
        break;
    }
    
    //If we are here, it means a selection was changed or a game started, or user did nothing
    if (selectionChanged){
      //For now, do nothing
    } else if (runSelection){//Start selected game
      switch (curSelection){
         case 1:
          Serial.println("Chattable Start");
          //Serial.println("Tetris Start");
          //ingame=1;
          //runTetris();
          //rgbmatrix();
          break;  
        case 2:
          Serial.println("Rainbow Start");
          //ingame=0;
          runRainbowPalette();
          break;
        case 3:
          Serial.println("Color Start");
          //ingame=0;
          runColorPalette();
          break;
        case 4:
          Serial.println("Stars Start");
          //ingame=0;
          runStars();
          break;
        case 5:
          Serial.println("VU Start");
          //ingame=0;
          runVUmeter();
          break;
        case 6:
          Serial.println("Dice Start");
          //ingame=0;
          runDice();
          break;     
        case 7:
          Serial.println("Snake Start");
          //clearcontrollerled();
          //led1[0] = CRGB::White;
          //led2[1] = CRGB::White;
          //led3[1] = CRGB::White;
          //led4[2] = CRGB::White;
          ingame=1;
          runSnake();
          break; 
        case 8:
          Serial.println("Pong Start");
          ingame=1;
          runPong();        
          break;  
        case 9:
          Serial.println("Bricks Start");
          //ingame=1;      
          runBricks();
          break;             
      }
    } else {
      //If we are here, no action was taken by the user, so we will move to the next selection automatically
      curSelection++;
      checkSelectionRange();
    }
  }
}

void checkSelectionRange(){
  if (curSelection>MAXSELECTION){
    curSelection = MINSELECTION;
  } else if (curSelection<MINSELECTION){
    curSelection = MAXSELECTION;
  }
}
