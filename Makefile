CXX = g++
INCLUDE_DIRS := $(shell find include -type d)
INCLUDE_FLAGS := $(patsubst %, -I%, $(INCLUDE_DIRS))

CXXFLAGS = -Wall -Wextra -std=c++11 -MMD -MP -I include

SRC := $(shell find src -name '*.cpp') main.cpp
OBJ := $(patsubst src/%.cpp, build/%.o, $(SRC))
OBJ := $(patsubst main.cpp, build/main.o, $(OBJ))
DEP := $(OBJ:.o=.d)

BIN = programa

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $@

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/main.o: main.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build $(BIN)

# Incluir dependencias, si existen
-include $(DEP)
