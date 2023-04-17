all:
	gcc -Iinclude/ src/ball.c src/game.c src/main.c src/pad.c src/pong.c src/texture.c -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lSDL2_ttf -lSDL2_image -lm -o pong.exe -Wall -Wextra -Wpedantic 

linux:
	gcc -Iinclude/ src/ball.c src/game.c src/main.c src/pad.c src/pong.c src/texture.c -lSDL2 -lGL -lSDL2_image -lm -o pong -Wall -Wextra -Wpedantic
