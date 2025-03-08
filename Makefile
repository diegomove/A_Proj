CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2


SRC = main.cc k-shingles.cc normalizeText.cc jaccard.cc minhash.cc
OBJ = $(SRC:.cc=.o)
DEPS = k-shingles.hh normalizeText.hh jaccard.hh minhash.hh

TARGET = ProjecteA

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
