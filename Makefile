CXX = g++
CXXFLAGS = -g -Wall `sdl2-config --cflags` `pkg-config --cflags SDL2_image` 
LDFLAGS = `sdl2-config --libs` `pkg-config --libs SDL2_image` `sdl2-config --libs` -lSDL2_ttf
TARGET = build/main

# Source files
SRCS = $(wildcard src/*.cpp)  # Automatically include all .cpp files in the src directory

# Default target
all: $(TARGET)

# Link and create the executable
$(TARGET): $(SRCS)
	mkdir -p build
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Clean target
clean:
	rm -rf build/*
