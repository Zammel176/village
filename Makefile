# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

# Source files (only .cpp)
SRC = main.cpp \
      Board.cpp \
      Building.cpp \
      ElixirCollector.cpp \
      Enemy.cpp \
      Entity.cpp \
      GoldMine.cpp \
      InputManager.cpp \
      Npc.cpp \
      Player.cpp \
      Position.cpp \
      ResourceGenerator.cpp \
      Resources.cpp \
      TownHall.cpp \
      Wall.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Target executable
TARGET = game

# Default: build the project
make: $(TARGET)

# Build executable from object files
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up
clear:
	rm -f $(OBJ) $(TARGET)

