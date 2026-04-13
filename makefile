# Variables
CXX = g++
STD = -std=c++20
TARGET = projekt
SRCS = $(wildcard *.cpp)
HDRS = $(wildcard *.hpp)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the object files
$(TARGET): $(OBJS)
	$(CXX) $(STD) -o $(TARGET) $(OBJS)

# Compile source files; now depends on HDRS
# If any .hpp file changes, all .o files will be rebuilt
%.o: %.cpp $(HDRS)
	$(CXX) $(STD) -c -Wall -Wextra -O3 $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
