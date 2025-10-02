    CXX=g++
    CXXFLAGS=-std=c++11 -Wall
    SRC=src
    TARGET=astucia_naval_V2

    all: $(TARGET)

    $(TARGET): $(SRC)/main.cpp $(SRC)/casilla.cpp $(SRC)/tablero.cpp $(SRC)/juego.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)/main.cpp $(SRC)/casilla.cpp $(SRC)/tablero.cpp $(SRC)/juego.cpp

    clean:
	rm -f $(TARGET)