#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define TRUE 1
#define FALSE 0

#define N 3

#define CELL_WIDTH (WINDOW_WIDTH / N)
#define CELL_HIGHT (WINDOW_HEIGHT / N)

typedef struct
{
    int board[N * N];
    int player;
    int state;
} game_t;

typedef enum
{
    RUNNING_STATE,
    PLAYER_X_WON,
    PLAYER_O_WON,
    TIE_STATE,
    QUIT_STATE
} STATE;

typedef enum
{
    EMPTY,
    PLAYER_X,
    PLAYER_O
} PLAYER;


void render_game(SDL_Renderer *renderer, const game_t *game, SDL_Texture *x_text, SDL_Texture *o_text);
void click_on_cell(game_t *game, int row, int column);

#endif
