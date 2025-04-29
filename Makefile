CXX = g++

# Default MAX_DATA value; override by running, e.g., `make MAX_DATA=2000000`
MAX_N ?= 10

CFLAGS = --std=c++17 -O3 -march=native -fopenmp -fopenmp-simd -DMAX_N=$(MAX_N)

# Target executable name and source files
TARGET = prog_cpp
SRCS = main.cpp

# Rule to build the target executable
$(TARGET): $(SRCS)
	$(CXX) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean up generated files
.PHONY: clean
clean:
	rm -f $(TARGET)
