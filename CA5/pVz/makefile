pvz: main.o menu.o play.o load_music.o load_sound.o  win.o gameover.o read_from_file.o gameplay.o line.o  square.o plant.o zombie.o bullet.o card.o sun.o
	g++ -std=c++20 main.o menu.o play.o load_music.o load_sound.o win.o read_from_file.o gameover.o gameplay.o line.o square.o bullet.o plant.o zombie.o card.o sun.o -o pvz.out  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main.o: main.cpp
	g++ -std=c++20 -c main.cpp

menu.o: menu.cpp
	g++ -std=c++20 -c menu.cpp

play.o: play.cpp
	g++ -std=c++20 -c play.cpp
	
load_music.o: load_music.cpp
	g++ -std=c++20 -c load_music.cpp
	
load_sound.o: load_sound.cpp
	g++ -std=c++20 -c load_sound.cpp

win.o: win.cpp
	g++ -std=c++20 -c win.cpp

gameover.o: gameover.cpp
	g++ -std=c++20 -c gameover.cpp

read_from_file.o: read_from_file.cpp
	g++ -std=c++20 -c read_from_file.cpp

gameplay.o: gameplay.cpp
	g++ -std=c++20 -c gameplay.cpp

line.o: line.cpp
	g++ -std=c++20 -c line.cpp

square.o: square.cpp
	g++ -std=c++20 -c square.cpp

bullet.o: bullet.cpp
	g++ -std=c++20 -c bullet.cpp

plant.o: plant.cpp
	g++ -std=c++20 -c plant.cpp

zombie.o: zombie.cpp
	g++ -std=c++20 -c zombie.cpp

card.o: card.cpp
	g++ -std=c++20 -c card.cpp

sun.o: sun.cpp
	g++ -std=c++20 -c sun.cpp

clean:
	rm *.o pvz.out

