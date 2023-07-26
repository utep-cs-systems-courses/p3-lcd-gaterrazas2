#include "msp430.h"
#include "game.h"
#include "buzzer.h"

short ballPos[2] = {screenWidth / 2, screenHeight / 2}; // start ball at the center
unsigned int ball_color = COLOR_WHITE;
short ball_direction[2] = {4, 4}; // Decrease for slower ball movement

static short play_sound;

short player1_pos = screenHeight / 2 - 10;
short player2_pos = screenHeight / 2 - 10;
unsigned int player1_color = COLOR_RED;
unsigned int player2_color = COLOR_BLUE;
unsigned int player1_score = 0;
unsigned int player2_score = 0;

// draws a tiny white rectangle
void draw_ball(int col, int row, unsigned short color)
{
    fillRectangle(col - 1, row - 1, 3, 3, color);
}

// Draw players 1 (red) and 2 (blue)
void draw_player1(int row, unsigned short color)
{
    fillRectangle(10, row, 3, 20, color);
}

void draw_player2(int row, unsigned short color)
{
    fillRectangle(screenWidth - 10 - 3, row, 3, 20, color);
}

// continously updates the position of the ball
void screen_update_ball()
{
    // Check if player 1 won the game (scored 3 points)
    if(player1_score >= 3){
        clearScreen(COLOR_WHITE);
        drawString5x7(40,75, "Red wins!", COLOR_RED, COLOR_WHITE);
        drawString5x7(40,85, "Game over", COLOR_BLACK, COLOR_WHITE);
        play_sound = (2 * 250);
        // plays sound
        buzzer_advance_frequency();
        
    }
    // Check if player 2 won the game (scored 3 points)
    else if(player2_score >= 3){
        clearScreen(COLOR_WHITE);
        drawString5x7(40,75, "Blue wins!", COLOR_BLUE, COLOR_WHITE);
        drawString5x7(40,85, "Game over", COLOR_BLACK, COLOR_WHITE);
        play_sound = (2 * 250);
        // plays sound
        buzzer_advance_frequency();
    }
    // if there is no winner yet
    else{
        // erase the previous ball position
        // this removes the tail the ball moving leaves
        draw_ball(ballPos[0], ballPos[1], COLOR_BLACK);
        
        // Update the ball position based on the ball direction
        // move it accordingly
        ballPos[0] += ball_direction[0];
        ballPos[1] += ball_direction[1];
        
        // Check collision with the top and bottom edges of the screen
        if (ballPos[1] <= 0 || ballPos[1] >= screenHeight)
            ball_direction[1] = -ball_direction[1]; // Reverse the vertical direction
        
        // Check collision with Player 1 paddle
        // checks if they are in the same position
        if (ballPos[0] <= 10 + 3 && ballPos[1] >= player1_pos && ballPos[1] <= player1_pos + 20)
            ball_direction[0] = -ball_direction[0]; // Reverse the horizontal direction
        
        // Check collision with Player 2 paddle
        // checks if they are in the same position
        if (ballPos[0] >= screenWidth - 10 - 3 && ballPos[1] >= player2_pos && ballPos[1] <= player2_pos + 20)
            ball_direction[0] = -ball_direction[0]; // Reverse the horizontal direction
        
        // Check if the ball goes beyond Player 1's paddle
        // to score points
        if (ballPos[0] <= 0)
        {
            player2_score++;
            ballPos[0] = screenWidth / 2;
            ballPos[1] = screenHeight / 2;
            ball_direction[0] = -ball_direction[0]; // Start from the center with the opposite horizontal direction
        }
        
        // Check if the ball goes beyond Player 2's paddle
        // to score points
        if (ballPos[0] >= screenWidth)
        {
            player1_score++;
            ballPos[0] = screenWidth / 2;
            ballPos[1] = screenHeight / 2;
            ball_direction[0] = -ball_direction[0]; // Start from the center with the opposite horizontal direction
        }
        
        draw_ball(ballPos[0], ballPos[1], ball_color); // draw the ball at the new position
    }
}

void screen_update_players()
{
    // Only update the parts of the screen that changed
    static short player1_pos_prev = -1;
    static short player2_pos_prev = -1;

    if (player1_pos != player1_pos_prev)
    {
        // preventing tail image
        fillRectangle(10, player1_pos_prev, 3, 20, COLOR_BLACK); // Erase previous Player 1
        draw_player1(player1_pos, player1_color); // draw updated Player 1
        player1_pos_prev = player1_pos;
    }

    if (player2_pos != player2_pos_prev)
    {
        fillRectangle(screenWidth - 10 - 3, player2_pos_prev, 3, 20, COLOR_BLACK); // Erase previous Player 2
        draw_player2(player2_pos, player2_color); // draw updated Player 2
        player2_pos_prev = player2_pos;
    }
}

void switch_init()
{
    // Setup the switches (SW1 - SW4) as inputs
    P2REN |= SWITCHES;
    P2OUT |= SWITCHES;
}

void update_game()
{
    // moves the ball and the updates the players
    screen_update_ball();
    screen_update_players();
}

