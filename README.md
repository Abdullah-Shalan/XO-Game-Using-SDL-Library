## Compile The Game
``` bash
gcc -Isrc/Include -Lsrc/lib -Wall -std=c99 -o game *.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
```

## run 
``` bash
game
```