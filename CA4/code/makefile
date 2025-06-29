CarWashManager: main.o car_wash.o stage.o car.o worker.o
	g++ -std=c++20 main.o car_wash.o stage.o car.o worker.o -o CarWashManager.out


main.o: main.cpp
	g++ -std=c++20 -c main.cpp

car_wash.o: car_wash.cpp
	g++ -std=c++20 -c car_wash.cpp

stage.o: stage.cpp
	g++ -std=c++20 -c stage.cpp

car.o: car.cpp
	g++ -std=c++20 -c car.cpp

worker.o: worker.cpp
	g++ -std=c++20 -c worker.cpp

clean:
	rm *.o CarWashManager.out
