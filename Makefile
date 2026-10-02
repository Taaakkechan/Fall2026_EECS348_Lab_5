CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET   = matrix_ops
SRC      = matrix_ops.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
