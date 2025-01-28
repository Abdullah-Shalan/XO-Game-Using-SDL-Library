
#include "game.h"

// constant colors for player x, player o, the tie and grid
const SDL_Color GRID_COLOR = {.r = 255, .g = 255, .b = 255};
const SDL_Color PLAYER_X_COLOR = {.r = 255, .g = 0, .b = 0};
const SDL_Color PLAYER_O_COLOR = {.r = 0, .g = 0, .b = 255};
const SDL_Color TIE_COLOR = {.r = 50, .g = 50, .b = 50};

// function to render the grid
void render_grid(SDL_Renderer *renderer, const SDL_Color *color)
{
    // set the renderer color to the grid color
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

    // loop to draw the grid with respect to cell size
    for (size_t i = 1; i < N; i++)
    {
        SDL_RenderDrawLine(renderer, i * CELL_WIDTH, 0, i * CELL_WIDTH, WINDOW_HEIGHT);
        SDL_RenderDrawLine(renderer, 0, i * CELL_HIGHT, WINDOW_WIDTH, i * CELL_HIGHT);
    }
}

void render_x_and_o(SDL_Renderer *renderer, int row, int column, SDL_Texture *text)
{
    // sdl rect to store the texture size and place
    SDL_Rect dest;

    // storing texture width and height
    SDL_QueryTexture(text, NULL, NULL, &dest.w, &dest.h);

    // scaling down to fit in a cell
    dest.h /= 4.5;
    dest.w /= 4.5;

    // equation so center texture in the cell
    dest.x = column * CELL_WIDTH + (CELL_WIDTH / 2 - dest.w / 2);
    dest.y = row * CELL_HIGHT + (CELL_HIGHT / 2 - dest.h / 2);

    // render the texture with respect to dest rect
    SDL_RenderCopy(renderer, text, NULL, &dest);
}

void render_game(SDL_Renderer *renderer, const game_t *game, SDL_Texture *x_text, SDL_Texture *o_text)
{
    // render the grid according to the state of the game
    switch (game->state)
    {
    case PLAYER_X_WON:
        render_grid(renderer, &PLAYER_X_COLOR);
        break;
    case PLAYER_O_WON:
        render_grid(renderer, &PLAYER_O_COLOR);
        break;
    case TIE_STATE:
        render_grid(renderer, &TIE_COLOR);
        break;
    
    default:
        render_grid(renderer, &GRID_COLOR);
        break;
    }

    // iterate over the board and render according to the correct player
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            switch (game->board[i * N + j])
            {
            case PLAYER_X:
                render_x_and_o(renderer, i, j, x_text);
                break;
            case PLAYER_O:
                render_x_and_o(renderer, i, j, o_text);
                break;

            default:
                break;
            }
        }
    }
}