#ifndef GAME_H
#define GAME_H

#include "lcdutils.h"
#include "lcddraw.h"

#define LED BIT6

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3

#define SWITCHES (SW1 | SW2 | SW3 | SW4)

extern short ballPos[2];
extern unsigned int ball_color;
extern short ball_direction[2];
extern short player1_pos;
extern short player2_pos;
extern unsigned int player1_color;
extern unsigned int player2_color;
extern unsigned int player1_score;
extern unsigned int player2_score;

void draw_ball(int col, int row, unsigned short color);
void draw_player1(int row, unsigned short color);
void draw_player2(int row, unsigned short color);
void screen_update_ball();
void screen_update_players();
void switch_init();
void update_game();

#endif /* GAME_H */
