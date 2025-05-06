# Makefile for building the pybind11-based femsolver module

CXX = g++

# 1. Get pybind11 include flags
PYBIND11_INC := $(shell python3 -m pybind11 --includes)

# 2. Get Python linker flags (includes libpython, etc.)
PY_LDFLAGS     := $(shell python3-config --ldflags)

# 3. Common compiler flags
CXXFLAGS      := -std=c++20 -O3 -march=native -fopenmp -fopenmp-simd -Wall -shared -fPIC $(PYBIND11_INC)
LDFLAGS       := $(PY_LDFLAGS)

# 4. Target module name with correct suffix (.so/.pyd)
TARGET        := outputs/femsolver$(shell python3-config --extension-suffix)

# 5. Source files
SRCS          := main_pybind.cpp

# Default target
all: $(TARGET)

# Build rule: compile & link in one step
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# Clean up
clean:
	rm -f $(TARGET)








