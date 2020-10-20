CXX ?= g++

SRC_PATH = src
BUILD_PATH = build
BIN_PATH = $(BUILD_PATH)/bin

BIN_NAME = codegen

SOURCES = $(shell find $(SRC_PATH) -name '*.cpp' | sort -k 1nr | cut -f2-)
OBJECTS = $(SOURCES:$(SRC_PATH)/%.cpp=$(BUILD_PATH)/%.o)
DEPS = $(OBJECTS:.o=.d)

COMPILE_FLAGS = -std=c++14 -Wall -Wextra -g
INCLUDES = -I include/ -I /usr/local/include/eigen3
LIBS =

.PHONY: default_target
default_target: release

.PHONY: release
release: dirs
	$(MAKE) all

.PHONY: dirs
dirs:
	mkdir -p $(dir $(OBJECTS))
	mkdir -p $(BIN_PATH)

.PHONY: clean
clean:
	$(RM) -r $(BUILD_PATH)
	$(RM) -r $(BIN_PATH)

.PHONY: all
all: $(BIN_PATH)/$(BIN_NAME)

# Creation of the executable
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) ${LIBS}

# Add dependency files, if they exist
-include $(DEPS)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) $(COMPILE_FLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
