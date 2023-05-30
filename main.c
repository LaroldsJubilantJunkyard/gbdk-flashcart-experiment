#include <gb/gb.h>
#include <gbdk/font.h>

#include <gbdk/console.h>
#include <stdio.h>
#include <stdint.h>

extern uint8_t chosenFile;
extern uint16_t chosenFileCheckSum;

uint8_t spot=0;
uint8_t joypadPrevious =0,joypadCurrent=0;

void main(void)
{

      font_t  min_font;

    /* First, init the font system */
    font_init();
    
    min_font = font_load(font_min);

    // Enable RAM bank 
    // The data in this bank is in non-violitle ram
    ENABLE_RAM;

  SWITCH_RAM(0);
    if(chosenFileCheckSum==12345){

            if(chosenFile==1)printf("Game: tetris\n");
            else printf("Game: 1942\n");

    DISABLE_RAM;
        printf("checksum is set\n");
            printf("ending loop\n");

    return;
       
    }else {


        printf("checksum not set\n");
        printf("use Left/Right\n");
        printf("to pick a game\n");
    DISABLE_RAM;
    }


    // Loop forever
    while(1) {

        joypadPrevious=joypadCurrent;
         joypadCurrent=joypad();

        if((joypadCurrent &J_RIGHT)&&!(joypadPrevious & J_RIGHT)){
            spot = (spot+1)%2;
            if(spot==1)printf("Game: tetris\n");
            else printf("Game: 1942\n");
        }
        if((joypadCurrent &J_LEFT)&&!(joypadPrevious & J_LEFT)){
            spot = spot==0?1:0;
            if(spot==1)printf("Game: tetris\n");
            else printf("Game: 1942\n");
        }
        if((joypadCurrent &J_A)&&!(joypadPrevious & J_A)){
            if(spot==1)printf("Game: tetris\n");
            else printf("Game: 1942\n");
            
                // Enable RAM bank 
                // The data in this bank is in non-violitle ram
                ENABLE_RAM;

            SWITCH_RAM(0);

            chosenFile=spot;
            chosenFileCheckSum = 12345;
                DISABLE_RAM;
            printf("checksum set\n");
            printf("ending loop\n");
            printf("close emulator\n");
                return;


        }


		// Game main loop processing goes here


		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
