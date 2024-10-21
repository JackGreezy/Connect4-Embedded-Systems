// Lab9Main.c
// Runs on MSPM0G3507
// Lab 9 solution
// Your name
// Last Modified: 11/6/2023

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "ADC1.h"
#include "DAC5.h"
#include "FIFO1.h"
#include "UART1.h"
#include "UART2.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h"


// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
   Clock_Init40MHz(); // run this line for 40MHz
//  Clock_Init80MHz(0);   // run this line for 80MHz
}

//buttons Init
void Button_Init(void){  //in text book go to page 74 table 2.2.2
     IOMUX->SECCFG.PINCM[PB17INDEX] = (uint32_t) 0x00040081; // sets pb17 to be an input 0x00040081: special code for making an input
     IOMUX->SECCFG.PINCM[PB16INDEX] = (uint32_t) 0x00040081; // input
}

uint32_t Button_In(void){
    uint32_t data = GPIOB->DIN31_0;
    uint32_t switchState = 0;
    data = (data&(0x38000)); //ask gives bit values for PB 17 16 15
    data >>= 15;


    if( (GPIOB->DIN31_0 & 1<<17) == 1<<17){
        switchState= 1;
    }
    if((GPIOB->DIN31_0 & 1<<16) == 1<<16){
           switchState= 2;
       }


        return switchState;
}



//Lab7 Stuff for slide pot:
#define ADCVREF_VDDA 0x000
#define ADCVREF_INT  0x200



uint32_t Data;
uint32_t Flag = 0;
// games  engine runs at 30Hz
void TIMG12_IRQHandler(void){
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
	  Data = ADCin();  // sample 12-bit ADC0 channel 5, slidepot
	  Flag = 1;
	  //reads slide pot
  }
}
uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage=English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[] ="Hello";
const char Hello_Spanish[] ="\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] ="All\x83";
const char Goodbye_English[]="Goodbye";
const char Goodbye_Spanish[]="Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";
const char Language_Portuguese[]="Portugu\x88s";
const char Language_French[]="Fran\x87" "ais";
const char *Phrases[3][4]={
  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
};

uint32_t player = 1; //1 corresponds to red, 2 corresponds to yellow

#define ROW_COUNT 6 // Number of rows
#define COLUMN_COUNT 7 // Number of columns

int matrix[ROW_COUNT][COLUMN_COUNT]; // Global matrix declaration

void initBoard(void) { // initializes connect4 matrix
    // Initializing the matrix elements to 0
    for(int i = 0; i < ROW_COUNT; i++) {
        for(int j = 0; j < COLUMN_COUNT; j++) {
            matrix[i][j] = 0;
        }
    }
    ST7735_DrawBitmap(0, 160, grid_new, 128, 160); // prints matrix to screen
}

//slidepot stuff
int32_t Position;    // 32-bit fixed-point

//int slidePot(int player){ // gives me number 0 to 2000
//
//        //now print disc to screen dependent on slide position
//
//        return Position;
//       }
//

//
//int ButtonPressed(uint32_t position){
//	//check if button is pressed
	//if no button pressed return
	//if exit button is pressed show pop up: are you sure you want to exit to main menu? Press X for yes, Y for no or something
	//if placement button is pressed, check if legal move!
	//if legal move then print graphics to screen and update matrix, increment move counter, return
	//if illegal move play doink noise and return

//next function for when button is pressed
//if(Position>=((2000/7)*6) && Position<=(2000)){//column 0
//    ST7735_DrawBitmap(0, 160, discColor, 5, 25);
//}
//else if(Position>=((2000/7)*5) && Position<=(2000/7)*6){//column 1
//	uint32_t column = 1;
//    ST7735_DrawBitmap(0, 160, discColor, 5+(18)*column, 25);
//}


//is move valid checker:

uint32_t MoveCheck(uint32_t position, uint32_t player){
	int column;
	if(Position>=((1900/7)*6) && Position<=(1900)){//column 0
			column = 0;
		}
	else if(Position>=((1900/7)*5) && Position<=((1900/7)*6)){
			column = 1;
		}
	else if(Position>=((1900/7)*4) && Position<=((1900/7)*5)){
			column = 2;
		}
	else if(Position>=((1900/7)*3) && Position<=((1900/7)*4)){
			column=3;
		}
	else if(Position>=((1900/7)*2) && Position<=((1900/7)*3)){
			column = 4;
		}
	else if(Position>=(1900/7) && Position<=((1900/7)*2)){
			column = 5;
		}
	else if(Position>=0 && Position<=(1900/7)){
			column = 6;
		}

	if(matrix[0][column]==0){//then we are good to place in that column!
		int row = 5;
		int placement = 0;

		while(placement == 0){
			if(matrix[row][column] == 0){//then we can place in that spot
				matrix[row][column] = player;
				placement = 1; //exit while loop
				if(player == 1){
					ST7735_DrawBitmap((column*18 +4), (48+ row*24), red_blue, 18, 25);
					return 1;
				}
				if(player == 2){
					ST7735_DrawBitmap((column*18 +4), (48+ row*24), yellow_blue, 18, 25);
					return 1;
				}
			}
				row = row-1; //decrement row value if we cannot place
		}
	}
		Sound_Explosion();
		return 0;
}

uint32_t PlayerSwitch(uint32_t player){
	if(player == 1){
		return 2;
	}
	else{
		return 1;
	}
}

int checkFor4(uint32_t player){
    int c, r;

    // Check horizontal locations for win
    for(c = 0; c < COLUMN_COUNT - 3; c++){
        for(r = 0; r < ROW_COUNT; r++){
            if(matrix[r][c] == player && matrix[r][c+1] == player && matrix[r][c+2] == player && matrix[r][c+3] == player){
                return 1;
            }
        }
    }

    // Check vertical locations for win
    for(c = 0; c < COLUMN_COUNT; c++){
        for(r = 0; r < ROW_COUNT-3; r++){
            if(matrix[r][c] == player && matrix[r+1][c] == player && matrix[r+2][c] == player && matrix[r+3][c] == player){
                return 1;
            }
        }
    }

    // Check positively sloped diagonals
    for(c = 0; c < COLUMN_COUNT-3; c++){
        for(r = 0; r < ROW_COUNT-3; r++){
            if(matrix[r][c] == player && matrix[r+1][c+1] == player && matrix[r+2][c+2] == player && matrix[r+3][c+3] == player){
                return 1;
            }
        }
    }

    // Check negatively sloped diagonals
    for(c = 0; c < COLUMN_COUNT-3; c++){
        for(r = 3; r < ROW_COUNT; r++){
            if(matrix[r][c] == player && matrix[r-1][c+1] == player && matrix[r-2][c+2] == player && matrix[r-3][c+3] == player){
                return 1;
            }
        }
    }

    return 0; // No win condition found
}


int MainMenu(void){
	  ST7735_FillScreen(0);       // set screen to black
	  ST7735_SetCursor(0,0);
	  ST7735_OutString("    Connect 4!\r   Press B1 For\r      English!\r Presione B2 para\r      espanol!");
	  uint32_t input;
	  while(1){
	  input = Button_In();
	  if(input==1){
		  Clock_Delay(8000000); // 100ms, to debounce switch
		  return 1; //english
	  }
	  if(input==2){
	  	Clock_Delay(8000000); // 100ms, to debounce switch
		  return 2; //spanish
	  }

	  }
}


int main(void){
	PLL_Init(); // set bus speed
	  Clock_Init80MHz(0);
	LaunchPad_Init();
	Button_Init(); //initializes the buttons
	ST7735_InitPrintf();
	Sound_Init();
	TimerG12_IntArm(2666667,3);
	//display main menu function
	__enable_irq();  //enable interrupt
	uint32_t mainMenuFlag = 1;
	while(1){
		while(mainMenuFlag==1){
	uint32_t language;
	language = MainMenu(); //if language is 1 english, language is 2 spanish
	mainMenuFlag = 0;

	uint32_t restartGameFlag = 1;
	while(restartGameFlag == 1){
	restartGameFlag = 0;

	while(Flag==0);
	Flag = 0;

	initBoard(); //initializes connect4 matrix
	uint32_t moveCounter = 0;
	uint32_t gameNotOver = 1; //1 means true
	uint32_t position;
	uint32_t isMoveValid = 0;
	uint32_t player = 1;
	uint32_t isGameOver = 0;
	uint32_t input; //for buttons
		SysTick->LOAD = 0xFFFFFF;    // max
		SysTick->VAL = 0;            // any write to current clears it
		SysTick->CTRL = 0x00000005;  // enable SysTick with core clock
		ADCinit(); //PB18 = ADC0 channel 5, slidepot
		while(isGameOver == 0){
			Position = Convert(Data);
			if(Position < 0){
				Position = 0;
			}
			if(Position>=0 && Position<1900){
			//check what player it is:
			if(player == 1){
				ST7735_DrawBitmap((-0.05368421052*Position +106), 25, red_white, 18, 25);
			}
			else if(player == 2){
				ST7735_DrawBitmap((-0.05368421052*Position +106), 25, yellow_white, 18, 25);
			}
			input = Button_In(); // Your Lab4 input
		    if(input == 1){ // place attempt
		    	isMoveValid = MoveCheck(Position,player);
		    	if(isMoveValid == 1){
		    		moveCounter = moveCounter+1;
		    		Sound_Shoot();
		    		if(moveCounter >= 7){
		    			isGameOver = checkFor4(player);
		    			if(isGameOver == 1){
		    				if(language==1){
		    					if(player == 1){
		    					    ST7735_SetCursor(0,0);
		    						ST7735_OutString("Player\r 1 Wins!\r  Press B1 To \r    Restart\r  Press B2 To \r  Return To Menu");
		    							    }
		    					if(player == 2){
		    					    ST7735_SetCursor(0,0);
		    						ST7735_OutString("Player\r 2 Wins!\r  Press B1 To \r    Restart\r  Press B2 To \r  Return To Menu");
		    							    }
		    				}
		    				if(language==2){
		    					if(player == 1){
		    					    ST7735_SetCursor(0,0);
		    						ST7735_OutString("El\r jugador 1 gana!\r  Presione B1 para \r     reiniciar\r  Presione B2 para \r     regresar al menu");
		    							   }
		    					if(player == 2){
		    					    ST7735_SetCursor(0,0);
		    						ST7735_OutString("El\r jugador 2 gana!\r  Presione B1 para \r     reiniciar\r  Presione B2 para \r     regresar al menu");
		    							   }
		    				}
		    				while(restartGameFlag==0 && mainMenuFlag==0){
			    				input = Button_In();
		    				if(input==1){
		    					restartGameFlag = 1;
		    						  }
		    				if(input==2){
		    					mainMenuFlag = 1;
		    						    }
		    						}
		    			}
		    		}
		    		if(moveCounter == 42){
		    			isGameOver = 1;
		    			if(language==1){
    					    ST7735_SetCursor(0,0);
		    				ST7735_OutString("  No Winner!\r  Press B1 To \r    Restart\r  Press B2 To \r  Return To Menu");
		    			}
		    			if(language==2){
    					    ST7735_SetCursor(0,0);
		    				ST7735_OutString("  Sin ganador!\r  Presione B1 para \r     reiniciar\r  Presione B2 para \r     regresar al menu");
		    			}
		    			while(restartGameFlag==0 && mainMenuFlag==0){
		    				input = Button_In();
		    			if(input==1){
		    				restartGameFlag = 1;
		    					     }
		    			if(input==2){
		    	               mainMenuFlag = 1;
		    				      }
		    					    }

		    			//show no winner menu restart or just print it
		    		}
		    		player = PlayerSwitch(player);
		    	}
			    Clock_Delay(8000000); // 100ms, to debounce switch
			}

			}
			ST7735_DrawBitmap((-0.05368421052*Position +106), 25, white, 18, 25);

		}
	}
	}
}
}

		//ButtonPressed(Position) // check if disc placement attempted by seeing if button is pressed, now check if it is legal move
//		if(moveCounter >= 7){
//			//call checkForConnect4, return gameOver = True or False
//			//if gameOver == True: print winner banner play noise, have play again banner or exit to main menu
//		}
//		if(moveCounter == 42){//end game, no winner play again banner or exit to main menu gameOver == True;
//
//		}
//






//
//
//
//// use main1 to observe special characters
//int main(void){ // main1
//    char l;
//  __disable_irq();
//  PLL_Init(); // set bus speed
//  LaunchPad_Init();
//  ST7735_InitPrintf();
//  ST7735_DrawBitmap(0, 160, grid_new, 128, 160);
//  ST7735_DrawBitmap(4, 160, red_blue, 18, 25);
//  ST7735_FillScreen(0x0000);            // set screen to black
//  for(phrase_t myPhrase=HELLO; myPhrase<= GOODBYE; myPhrase++){
//    for(Language_t myL=English; myL<= French; myL++){
//         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
//      ST7735_OutChar(' ');
//         ST7735_OutString((char *)Phrases[myPhrase][myL]);
//      ST7735_OutChar(13);
//    }
//  }
//  Clock_Delay1ms(3000);
//  ST7735_FillScreen(0x0000);       // set screen to black
//  l = 128;
//  while(1){
//    Clock_Delay1ms(2000);
//    for(int j=0; j < 3; j++){
//      for(int i=0;i<16;i++){
//        ST7735_SetCursor(7*j+0,i);
//        ST7735_OutUDec(l);
//        ST7735_OutChar(' ');
//        ST7735_OutChar(' ');
//        ST7735_SetCursor(7*j+4,i);
//        ST7735_OutChar(l);
//        l++;
//      }
//    }
//  }
//}
//
//// use main2 to observe graphics
//int main2(void){ // main2
//  __disable_irq();
//  PLL_Init(); // set bus speed
//  LaunchPad_Init();
//  ST7735_InitPrintf();
//    //note: if you colors are weird, see different options for
//    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
//  ST7735_FillScreen(ST7735_BLACK);
//  ST7735_DrawBitmap(22, 159, PlayerShip0, 18,8); // player ship bottom
//  ST7735_DrawBitmap(53, 151, Bunker0, 18,5);
//  ST7735_DrawBitmap(42, 159, PlayerShip1, 18,8); // player ship bottom
//  ST7735_DrawBitmap(62, 159, PlayerShip2, 18,8); // player ship bottom
//  ST7735_DrawBitmap(82, 159, PlayerShip3, 18,8); // player ship bottom
//  ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16,10);
//  ST7735_DrawBitmap(20,9, SmallEnemy10pointB, 16,10);
//  ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16,10);
//  ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16,10);
//  ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);
//
//  for(uint32_t t=500;t>0;t=t-5){
//    SmallFont_OutVertical(t,104,6); // top left
//    Clock_Delay1ms(50);              // delay 50 msec
//  }
//  ST7735_FillScreen(0x0000);   // set screen to black
//  ST7735_SetCursor(1, 1);
//  ST7735_OutString("GAME OVER");
//  ST7735_SetCursor(1, 2);
//  ST7735_OutString("Nice try,");
//  ST7735_SetCursor(1, 3);
//  ST7735_OutString("Earthling!");
//  ST7735_SetCursor(2, 4);
//  ST7735_OutUDec(1234);
//  while(1){
//  }
//}
//
//// use main3 to test switches and LEDs
//int main3(void){ // main3
//  __disable_irq();
//  PLL_Init(); // set bus speed
//  LaunchPad_Init();
//  Switch_Init(); // initialize switches
//  LED_Init(); // initialize LED
//  while(1){
//    // write code to test switches and LEDs
//    uint32_t data = Switch_In();
//    if(data == 0) LED_Off((1<<26)|(1<<25)|(1<<24));
//    if(data == 1) LED_On(1<<26);
//    if(data == 2) LED_On(1<<25);
//    if(data == 4) LED_On(1<<24);
//    if(data == 8) LED_On((1<<26)|(1<<25)|(1<<24));
//  }
//}
//// use main4 to test sound outputs
//int main4(void){ uint32_t last=0,now;
//  __disable_irq();
//  PLL_Init(); // set bus speed
//  LaunchPad_Init();
//  Switch_Init(); // initialize switches
//  LED_Init(); // initialize LED
//  Sound_Init();  // initialize sound
//  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
//  __enable_irq();
//  while(1){
//    now = Switch_In(); // one of your buttons
//    if((last == 0)&&(now == 1)){
//      Sound_Shoot(); // call one of your sounds
//    }
//    if((last == 0)&&(now == 2)){
//      Sound_Killed(); // call one of your sounds
//    }
//    if((last == 0)&&(now == 4)){
//      Sound_Explosion(); // call one of your sounds
//    }
//    if((last == 0)&&(now == 8)){
//      Sound_Fastinvader1(); // call one of your sounds
//    }
//    last = now;
//    // modify this to test all your sounds
//  }
//}
//// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
//int main5(void){ // final main
//  __disable_irq();
//  PLL_Init(); // set bus speed
//  LaunchPad_Init();
//  UART1_Init(); // just transmit, PA8, blind synchronization
//  UART2_Init(); // just receive, PA22, receiver timeout synchronization
//  ST7735_InitPrintf();
//    //note: if you colors are weird, see different options for
//    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
//  ST7735_FillScreen(ST7735_BLACK);
//  ADCinit();     //PB18 = ADC1 channel 5, slidepot
//  Switch_Init(); // initialize switches
//  LED_Init();    // initialize LED
//  Sound_Init();  // initialize sound
//  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
//  // initialize interrupts on TimerG12 at 30 Hz
//  // initialize all data structures
//  __enable_irq();
//
//  while(1){
//    // wait for semaphore
//       // clear semaphore
//       // update ST7735R
//    // check for end game or level switch
//  }
//}
