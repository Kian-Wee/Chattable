/*
void initDice() {
	clearTablePixels();
	clearcontrollerled();
}

void runDice() {
  initDice();
  unsigned long prevUpdateTime = 0;
  unsigned long curTime = 0;

   while(diceRunning) {
      
    if (diceMath) {
       // Clear pixels
      for (int i = 0; i < FIELD_WIDTH * FIELD_HEIGHT; i++)
        setPixel(i, 0);
      
      for(int i=0;i< MATH_ANIMATION;i++) {
        switch (random(6)) {
        case 0:
          printDice(diceOne);
          break;
        case 1:
          printDice(diceTwo);
          break;
        case 2:
          printDice(diceThree);
          break;
        case 3:
          printDice(diceFour);
          break;
        case 4:
          printDice(diceFive);
          break;
        case 5:
          printDice(diceSix);
          break;
        }
        delay(100);
      }
    }
    diceMath = false;
   
    do{
        readInput();
      if (curControl == BTN_EXIT){
        diceRunning = false;
        break;
      }
      else if (curControl == BTN_START) {
        diceMath = true;
      }
      curTime = millis();
      delay(10);
    }
    while ((curTime - prevUpdateTime) <20);//Once enough time  has passed, proceed. The lower this number, the faster the game is
    prevUpdateTime = curTime;
   }
}

//hard
void printColors(){
	long c1;
	long c2;
	long c3;
	long randomchosen;
	randomchosen=random(1,3);
	
	if(randomchosen==1){
		c1=34;
		c2=33;
		c3=33;
	}else if(randomchosen==2){
		c1=33;
		c2=34;
		c3=33;
	}else{
		c1=33;
		c2=33;
		c3=34;
		}
	
	int i=0;
	for(int t=0; t < 100; t++){
		long randomint;
		randomint=random(1,3);
		if(c1!=0&&c2!=0&&c2!=0){
			if(randomint=1){
				//setTablePixel(y,x, RED);
				leds[i] = CRGB::Red;
				c1--;
			}
			else if(randomint=2){
				leds[i] = CRGB::Blue;
				c2--;
			}
			else if(randomint=3){
				leds[i] = CRGB::Green;
				c3--;
			}
			i++;
		}else{
			
		}
	}
  showPixels();
}
*/
