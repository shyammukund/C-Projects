
# Usage
#   make 
#       Creates the executable $(TARGET) without AddressSanitizer.
#
#   make clean
#       Removes all the generated files (e.g., object files and executables).
#
#   make test
#       Creates the executable $(TEST_TARGET) using main_test.cpp without AddressSanitizer.
#
#   make asan
#       Creates the executable $(TARGET) with AddressSanitizer enabled.
#
#   make test_asan
#       Creates the executable $(TEST_TARGET) using main_test.cpp with AddressSanitizer enabled.

# Determine the C++ compiler
ifneq ($(shell which clang++),)
    CXX = clang++
else ifneq ($(shell which g++),)
    CXX = g++
else
    $(error No suitable C++ compiler found. Please install clang++ or g++.)
endif

# Specify the path to the Catch2 headers explicitly
CATCH2_INCLUDE = -I/usr/local/include/catch2/v2.13.7

# Compiler flags
CXXFLAGS = -g -std=c++17 -pedantic -Wall -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable 

# Target executable
TARGET = main
TEST_TARGET = test_main

# Source files
SRCS = main.cpp deque.cpp
TEST_SRCS = main_test.cpp deque.cpp

# Object files directory
OBJDIR = ./objs
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
TEST_OBJS = $(TEST_SRCS:%.cpp=$(OBJDIR)/%.o)

# Default rule to build the executable without AddressSanitizer
all: $(TARGET)

# Rule to build the executable from object files without AddressSanitizer
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build the test executable without AddressSanitizer
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(CATCH2_INCLUDE) -o $(TEST_TARGET) $(TEST_OBJS)

# Rule to build and produce the test binary without AddressSanitizer
test: $(TEST_TARGET)
	@echo "Test binary '$(TEST_TARGET)' has been built."

# Rule to build the executable with AddressSanitizer
asan: CXXFLAGS += -fsanitize=address -fsanitize=undefined
asan: $(TARGET)
	@echo "ASan binary '$(TARGET)' has been built."

# Rule to build the test executable with AddressSanitizer
test_asan: CXXFLAGS += -fsanitize=address -fsanitize=undefined
test_asan: $(TEST_TARGET)
	@echo "ASan test binary '$(TEST_TARGET)' has been built."

# Rule to build object files from source files
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(CATCH2_INCLUDE) -c $< -o $@

# Create object files directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean up generated files
clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJS) $(TEST_OBJS)
	rm -rf $(OBJDIR)

# Phony targets
.PHONY: all clean asan test test_asan
