# Compiler
CXX = g++

# Compiler and linker flags
CXXFLAGS = -g -Wall `sdl2-config --cflags` `pkg-config --cflags SDL2_image`
LDFLAGS = `sdl2-config --libs` `pkg-config --libs SDL2_image` -lSDL2_ttf

# Target executable
TARGET = build/main

# Source files (all .cpp recursively)
SRC = $(shell find . -name '*.cpp')

# Object files placed in build/src/ directory, mirroring source structure
OBJ = $(patsubst %.cpp, build/%.o, $(SRC))

# Header files (optional for dependency tracking)
HDR = $(shell find . -name '*.h')

# Default rule
all: $(TARGET)

# Linking the object files to create the final executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compiling source files into object files
# This rule handles .cpp files in subdirectories and places .o in build/
build/%.o: %.cpp $(HDR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove object files and the executable
clean:
	rm -rf build/*