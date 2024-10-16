CXX = g++
CXXFLAGS = -g -Wall `sdl2-config --cflags` `pkg-config --cflags SDL2_image`
LDFLAGS = `sdl2-config --libs` `pkg-config --libs SDL2_image`
TARGET = build/main

# Source files
SRC = src/main.cpp

# Default target
all: $(TARGET)

# Link and create the executable
$(TARGET): $(SRC)
	mkdir -p build
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^ $(LDFLAGS)

# Clean target
clean:
	rm -rf build/*
