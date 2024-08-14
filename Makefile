# Usage
#		make 
#		       	Creates the executable $(TARGET)
#
#		make clean
#		       	removes all the generated file, (e.g. obj and exe)
#


# Determine the C++ compiler
ifneq ($(shell which clang++),)
    CXX = clang++
else ifneq ($(shell which g++),)
    CXX = g++
else
    $(error No suitable C++ compiler found. Please install clang++ or g++.)
endif

# Compiler flags
CXXFLAGS = -std=c++14 -pedantic -Wall -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable

# Target executable
TARGET = main

# Source files
SRCS = main.cpp deque.cpp

# Object files directory
OBJDIR = ./objs
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

# Default rule to build the executable
all: $(TARGET)

# Rule to build the executable from object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files from source files
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create object files directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean up generated files
clean:
	rm -f $(TARGET) $(OBJS)
	rm -rf $(OBJDIR)

# Phony targets
.PHONY: all clean
