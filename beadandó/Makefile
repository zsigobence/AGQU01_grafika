all:
	gcc -Iinclude/ src/app.c src/button.c src/camera.c src/main.c src/flag.c  src/scene.c src/texture.c src/utils.c src/walls.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lobj -lopengl32 -lglu32 -lm -o beadando.exe -Wall -Wextra -Wpedantic -g

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/flag.c   src/scene.c src/texture.c src/utils.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o beadando -Wall -Wextra -Wpedantic
