#include <gb/gb.h>
#include <gbdk/font.h>

#include <gbdk/console.h>
#include <stdio.h>
#include <stdint.h>

extern uint8_t chosenFile;
extern uint16_t chosenFileCheckSum;
extern uint8_t romCount;
extern unsigned char romFileNames[2100];

uint8_t spot=0;
uint8_t max = 0;
uint8_t joypadPrevious =0,joypadCurrent=0;

const unsigned char test_string[20]= "this is the ul";

void main(void)
{

      font_t  min_font;

    /* First, init the font system */
    font_init();
    
    min_font = font_load(font_min);

    printf("0 is %u\n",'0');
    printf("9 is %u\n",'9');
    printf("a is %u\n",'a');
    printf("z is %u\n",'z');

    // Enable RAM bank 
    // The data in this bank is in non-violitle ram
    ENABLE_RAM;

  SWITCH_RAM(0);

    max = romCount;


    if(chosenFileCheckSum==12345){

            printf("Game: %s\n",romFileNames[chosenFile*21]);

    DISABLE_RAM;
        printf("checksum is set\n");
            printf("ending loop\n");

    return;
       
    }else {


        printf("checksum not set\n");
        printf("found %u games\n",romCount);
        printf("use Left/Right\n");
        printf("to pick a game\n");
        chosenFileCheckSum=0;
        chosenFile=0;
    DISABLE_RAM;
    }


    // Loop forever
    while(1) {

        joypadPrevious=joypadCurrent;
         joypadCurrent=joypad();

        if((joypadCurrent &J_RIGHT)&&!(joypadPrevious & J_RIGHT)){
            spot = (spot+1)%max;
                // Enable RAM bank 
                // The data in this bank is in non-violitle ram
                ENABLE_RAM;
                printf("Game ");
                for(uint8_t i=0;i<romFileNames[spot*21]+1;i++){
                    printf("%c",romFileNames[spot*21+i]);
                }
                printf("\n");
                DISABLE_RAM;
        }
        if((joypadCurrent &J_LEFT)&&!(joypadPrevious & J_LEFT)){
            spot = spot==0?(max-1):0;
                // Enable RAM bank 
                // The data in this bank is in non-violitle ram
                ENABLE_RAM;
                printf("Game ");
                for(uint8_t i=0;i<romFileNames[spot*21]+1;i++){
                    printf("%c",romFileNames[spot*21+i]);
                }
                printf("\n");
                DISABLE_RAM;
        }
        if((joypadCurrent &J_A)&&!(joypadPrevious & J_A)){
                // Enable RAM bank 
                // The data in this bank is in non-violitle ram
                ENABLE_RAM;
                printf("Game ");
                for(uint8_t i=0;i<romFileNames[spot*21]+1;i++){
                    printf("%c",romFileNames[spot*21+i]);
                }
                printf("\n");
            
            

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
