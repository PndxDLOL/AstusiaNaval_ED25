CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -O2
SRC = $(wildcard src/*.cpp)
TARGET = astucia_naval

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $(TARGET)

clean:
	rm -f $(TARGET) savegame.bin
