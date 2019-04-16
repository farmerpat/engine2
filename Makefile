# clear to turn off debugging
DEBUG=-g -O0

# user some variables (e.g. OBJECTS) to clean this nonsense up

all: util.o game_manager.o sprite.o controller.o hero_controller.o hero_sprite.o textured_sprite.o primitive_sprite.o rectangular_primitive_sprite.o level.o main.o
	g++ $(DEBUG) -o main util.o game_manager.o sprite.o controller.o hero_controller.o hero_sprite.o textured_sprite.o primitive_sprite.o rectangular_primitive_sprite.o level.o main.o -lSDL2 -lSDL2_image

controller.o: controller.cpp
	g++ $(DEBUG) -c controller.cpp -I /usr/include/SDL2 -lSDL2

util.o: util.cpp
	g++ $(DEBUG) -c util.cpp -I/usr/include/SDL2 -lSDL2

game_manager.o: game_manager.cpp
	g++ $(DEBUG) -c game_manager.cpp -I/usr/include/SDL2 -lSDL2

sprite.o: sprite.cpp util.o controller.o
	g++ $(DEBUG) -c sprite.cpp -I/usr/include/SDL2 -lSDL2 -lSDL2_image

hero_controller.o: hero_controller.cpp game_manager.o controller.o sprite.o
	g++ $(DEBUG) -c hero_controller.cpp -I/usr/include/SDL2 -lSDL2 -lSDL2_image

hero_sprite.o: hero_sprite.cpp sprite.o hero_controller.o
	g++ $(DEBUG) -c hero_sprite.cpp -I/usr/include/SDL2 -lSDL2 -lSDL2_image

textured_sprite.o: textured_sprite.cpp sprite.o
	g++ $(DEBUG) -c textured_sprite.cpp -I/usr/include/SDL2 -lSDL2 -lSDL2_image

primitive_sprite.o: primitive_sprite.cpp sprite.o
	g++ $(DEBUG) -c primitive_sprite.cpp -I/usr/include/SDL2 -lSDL2 -lSDL2_image

rectangular_primitive_sprite.o: rectangular_primitive_sprite.cpp primitive_sprite.o
	g++ $(DEBUG) -c rectangular_primitive_sprite.cpp -I/usr/include/SDL2 -lSDL2 -lSDL2_image

level.o: level.cpp sprite.o controller.o
	g++ $(DEBUG) -c level.cpp -I/usr/include/SDL2 -lSDL2

main.o: main.cpp
	g++ $(DEBUG) -c main.cpp -I/usr/include/SDL2 -lSDL2 -lSDL2_image

clean:
	rm *.o
