#include "game.h"

// check if the win condition is satisfied for a player
int check_player_won(game_t *game, int player)
{
    int row_count = 0, column_count = 0;
    int diag1_count = 0, diag2_count = 0;

    for (size_t i = 0; i < N; i++)
    {
        // count row and column for player
        for (size_t j = 0; j < N; j++)
        {
            if (game->board[i * N + j] == player)
                row_count++;

            if (game->board[j * N + i] == player)
                column_count++;
        }

        // player won if the count of row or column is 3
        if (row_count == N || column_count == N)
            return TRUE;

        // resets the counters for the next iteration
        row_count = 0;
        column_count = 0;

        // count diagonally
        if (game->board[i * N + i] == player)
            diag1_count++;
        if (game->board[i * N + N - i - 1] == player)
            diag2_count++;
    }

    // check if player won in the diagonals
    if ((diag1_count == 3 || diag2_count == 3))
    {
        return TRUE;
    }

    return FALSE;
}

// function to make sure there are available cells to play in 
int count_cells(const int *board, int cell)
{
    int count = 0;

    for (size_t i = 0; i < N * N; i++)
        if (board[i] == cell)
            count++;

    return count;
}

// check if (x or o) won, and if a tie occurred
// then changing the state accordingly
void check_game_over(game_t *game)
{
    if (check_player_won(game, PLAYER_X))
        game->state = PLAYER_X_WON;
    else if (check_player_won(game, PLAYER_O))
        game->state = PLAYER_O_WON;
    else if (count_cells(game->board, EMPTY) == 0)
        game->state = TIE_STATE;
}

void player_turn(game_t *game, int row, int column)
{
    if (game->board[row * N + column] == EMPTY)
    {
        // change the cell with the corresponding player
        game->board[row * N + column] = game->player;

        // switch the players turn
        if (game->player == PLAYER_X)
            game->player = PLAYER_O;
        else
            game->player = PLAYER_X;

        // check if the game ended
        check_game_over(game);
    }
}

// reset game by changing the state to running and making board array EMPTY
void reset_game(game_t *game)
{
    game->state = RUNNING_STATE;
    game->player = PLAYER_X;

    for (size_t i = 0; i < N * N; i++)
        game->board[i] = EMPTY;
}

// checks if the game is running then go-to player turn or reset the game otherwise
void click_on_cell(game_t *game, int row, int column)
{
    if (game->state == RUNNING_STATE)
    {
        player_turn(game, row, column);
    }
    else
    {
        reset_game(game);
    }
}