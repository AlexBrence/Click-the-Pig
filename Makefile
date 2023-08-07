CXXFLAGS := -I./include

.PHONY: all build run clean debug

all: build run

build: src/*.cpp
	g++ $(CXXFLAGS) $^ -o build/program -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

run: build
	./build/program

debug: src/*.cpp
	g++ -g $(CXXFLAGS) $^ -o debug/program -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf build/* debug/*
