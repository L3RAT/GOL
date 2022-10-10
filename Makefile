all: 
	gcc -Wall --pedantic src/main.c src/util.c src/game.c src/pnggen.c -o GoL -L/usr/lib/x86_64-linux-gnu/ -lpng

test: all
	./GoL data/test_pulsar 3 10

figure_eight: all
	./GoL data/test_figure_eight 8

fountain: all
	./GoL data/test_fountain 8

galaxy: all
	./GoL data/test_galaxy 5

gospel_gun: all
	./GoL data/test_gospel_gun 100

pentadecathlon: all
	./GoL data/test_pentadecathlon 15

pulsar: all
	./GoL data/test_pulsar 3

error1: all
	./GoL 

error2: all
	./GoL data/test_error2

error3: all
	./GoL data/test_error3

	
