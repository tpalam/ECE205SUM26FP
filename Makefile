CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra

SFML_PATH = /opt/homebrew/opt/sfml@2


INCLUDES = -I$(SFML_PATH)/include \
			-I/opt/homebrew/opt/nlohmann-json/include
LIBRARY_PATH = -L$(SFML_PATH)/lib
LIBRARIES = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

TARGET = game

SOURCES = main.cpp Game.cpp Player.cpp Platform.cpp Spike.cpp SawBlade.cpp FinishLine.cpp Level.cpp ObjectFactory.cpp Background.cpp SpeedBoost.cpp SlowDown.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCES) -o $(TARGET) $(LIBRARY_PATH) $(LIBRARIES)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)