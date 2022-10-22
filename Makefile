BIN=squares

all : $(BIN)

$(BIN) : $(wildcard ./src/*.c)
	gcc -o ./build/$@ $^ -lX11 -lpthread -lXinerama -lXext -lGL -g -lm -ldl

run :
	./build/$(BIN)

debug :
	gdb ./build/$(BIN)

clean :
	rm -rf *.o *~ ./build/$(BIN)
