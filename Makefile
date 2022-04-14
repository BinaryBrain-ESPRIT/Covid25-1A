game:main.o Main_Fn.o Text_Image.o Game.o Mouse.o ennemy.o player.o Background.o minimap.o enigme_image.o enigme.o
	gcc main.o Main_Fn.o Text_Image.o Game.o Mouse.o ennemy.o  player.o Background.o  minimap.o enigme_image.o enigme.o -g -o game -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
main.o:main.c 
	gcc -c main.c -g
Main_Fn.o:Main_Fn.c  
	gcc -c Main_Fn.c -g
Text_Image.o:Text_Image.c 
	gcc -c Text_Image.c  -g
Game.o:Game.c
	gcc -c Game.c  -g
Mouse.o:Mouse.c
	gcc -c Mouse.c -g
ennemy.o:ennemy.c
	gcc -c ennemy.c -g
player.o:player.c
	gcc -c player.c -g
Background.o:Background.c
	gcc -c Background.c -g
minimap.o:minimap.c
	gcc -c minimap.c -g
enigme_image.o:enigme_image.c
	gcc -c enigme_image.c -g
enigme.o:enigme.c
	gcc -c enigme.c -g 