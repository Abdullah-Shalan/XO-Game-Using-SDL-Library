
#include "game.h"


int main(int argc, char *argv[])
{

    // initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO ) != 0)
    {
        fprintf(stderr, "Error in initializing SDL : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // create window
    SDL_Window *window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_BORDERLESS);

    if (!window)
    {
        fprintf(stderr, "error in creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // crate a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED |
                                                    SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        fprintf(stderr, "error in creating renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // initializing SDL_images
    if (!IMG_Init(IMG_INIT_JPG))
    {
        fprintf(stderr, "error in initializing SDL_image : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // load the (x,o) images into memory using SDL_image
    SDL_Surface *x_surface = IMG_Load("Images/x.png");
    SDL_Surface *o_surface = IMG_Load("Images/o.png");

    if (!x_surface || !o_surface)
    {
        fprintf(stderr, "error in creating surface : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // load the images into GPU memory
    SDL_Texture *x_text = SDL_CreateTextureFromSurface(renderer, x_surface);
    SDL_Texture *o_text = SDL_CreateTextureFromSurface(renderer, o_surface);

    // free surface, because it's no longer needed
    SDL_FreeSurface(x_surface);
    SDL_FreeSurface(o_surface);

    if (!x_text || !o_text)
    {
        fprintf(stderr, "error in creating texture : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // create game state instance
    game_t game = {
        .board = {EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY},
        .player = PLAYER_X,
        .state = RUNNING_STATE};

    // Handle Event
    SDL_Event event;
    while (game.state != QUIT_STATE)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                game.state = QUIT_STATE;
                break;

            case SDL_MOUSEBUTTONDOWN:
                click_on_cell(&game,
                              event.button.y / CELL_HIGHT,
                              event.button.x / CELL_WIDTH);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    game.state = QUIT_STATE;
                break;

            default:
                break;
            }
        }

        // set the renderer color to black and clean the window with it
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // call render_game() to handle the frame rendering
        render_game(renderer, &game, x_text, o_text);

        
        // render the frame
        SDL_RenderPresent(renderer);
    }

    // clean up before exiting
    SDL_DestroyTexture(x_text);
    SDL_DestroyTexture(o_text);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
