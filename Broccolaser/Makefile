all: test

test: main.o Game.o Entity.o Background.o Player.o EnvironmentObject.o Camera.o
		g++ main.o Entity.o Player.o Background.o Game.o EnvironmentObject.o Camera.o -o test -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

Game.o: Game.cpp
	g++ -c --std=c++11 Game.cpp

Entity.o: Entity.cpp
	g++ -c --std=c++11 Entity.cpp

Background.o: Background.cpp
	g++ -c --std=c++11 Background.cpp

Player.o: Player.cpp
	g++ -c --std=c++11 Player.cpp

main.o: main.cpp 
	g++ -c --std=c++11 main.cpp
	
EnvironmentObject.o: EnvironmentObject.cpp
	g++ -c --std=c++11 EnvironmentObject.cpp

Camera.o: Camera.cpp
	g++ -c --std=c++11 Camera.cpp