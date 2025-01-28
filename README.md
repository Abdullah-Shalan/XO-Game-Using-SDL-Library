# XO Game Using SDL Library

## Description
This repository contains a Tic Tac Toe (XO) game implemented in C using the SDL (Simple DirectMedia Layer) library.  
The game provides a simple graphical interface. It utilizes SDL for rendering graphics and handling user inputs.

## Features
- Two-player Tic Tac Toe game.
- Graphical interface built using the SDL library.
- Handles player turns and determines the winner or a draw.

## Installing SDL Libraries
- The library is already installed in the `src` directory
- Ensure the SDL `.dll` files are in the same directory as the compiled executable for the game to run.

## Compilation
To compile the game, use the following command:

```bash
gcc -Isrc/Include -Lsrc/lib -Wall -std=c99 -o game *.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
```

## Running the Game
After successful compilation, execute the `game` file:

```bash
./game
```

## How to Play
1. Run the game using the `game.exe` file.
2. The game starts with Player 1 (X) and alternates turns with Player 2 (O).
3. Click on a grid cell to place your marker.
4. The game ends when:
   - A player gets three markers in a row (horizontal, vertical, or diagonal).
   - The board is full, resulting in a draw.
5. press `ESC` key to close the game

## Project Workflow
The game is structured into three main components:

1. **Game Logic**:
   - Implemented in `logic.c`.
   - Tracks the game state, including the positions of Xs and Os.
   - Checks for win conditions by evaluating rows, columns, and diagonals.
   - Detects draw conditions when the board is full without a winner.

2. **Rendering**:
   - Handled in `renderin.c`.
   - Draws the game board, Xs, and Os on the screen.
   - Updates the display after each player's move.

3. **Main Program**:
   - Defined in `main.c`.
   - Initializes SDL, sets up the game window, and manages the game loop.
   - Processes user inputs, updates the game state, and calls rendering functions.

## Dependencies
- *SDL2*
- *SDL2_image*

## Files
- **`main.c`**: The entry point of the program, handling the game loop and rendering.
- **`logic.c`**: Contains the game logic, including checking for a winner or a draw.
- **`renderin.c`**: Handles rendering the game board and updates to the screen.
- **`game.h`**: Header file with declarations for game logic and rendering functions.
- **`SDL2.dll` and `SDL2_image.dll`**: SDL library files required to run the game.


## Acknowledgments
Special thanks to the SDL community for their documentation and resources.