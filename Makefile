# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -Wall -g

# Target executable name
TARGET = game

# Source files
SOURCES = main.cpp cards.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Compile the project
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile each source file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(TARGET) $(OBJECTS)
