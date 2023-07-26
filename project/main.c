#include "msp430.h"
#include "game.h"
#include "buzzer.h"
#include <libTimer.h>

short redrawScreen = 1;
short i = 0;

void wdt_c_handler()
{
    static int secCount = 0;

    secCount++;
    if (secCount >= 25)
    { // Update ball and players 10/sec
    
      if (!(P2IN & SW2))
      {
        // Move Player 1 down, ensuring it doesn't go below the screen
        if (player1_pos < screenHeight - 20)
          player1_pos+= 5;
      }
      else if (!(P2IN & SW1))
      {
        // Move Player 1 up, ensuring it doesn't go above the screen
        if (player1_pos > 0)
          player1_pos-=5;
      }

      if (!(P2IN & SW4))
      {
        // Move Player 2 down, ensuring it doesn't go below the screen
        if (player2_pos < screenHeight - 20)
          player2_pos+=5;
      }
      else if (!(P2IN & SW3))
      {
        // Move Player 2 up, ensuring it doesn't go above the screen
        if (player2_pos > 0)
          player2_pos-=5;
      }

      redrawScreen = 1;
      secCount = 0;
    }
}

void main()
    {
      P1DIR |= LED;
      P1OUT |= LED;

      configureClocks();
      lcd_init();
      switch_init();
      buzzer_init();

      enableWDTInterrupts();
      or_sr(0x8);

      clearScreen(COLOR_BLACK); // Set the background to black
    
      // continue to run the game 
      while (1)
      {
        if (redrawScreen)
        {
          redrawScreen = 0;
          update_game();
        }
        P1OUT &= ~LED;
        or_sr(0x10);
        P1OUT |= LED;
      }
    }
