CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

SRC = main.cc k-shingles.cc normalizeText.cc jaccard.cc minhash.cc normalizeText2.cc permutacions.cc stopwords.cc
OBJ = $(SRC:.cc=.o)

TARGET = ProjecteA

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cc k-shingles.hh normalizeText.hh jaccard.hh minhash.hh normalizeText2.hh permutacions.hh stopwords.hh
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

k-shingles.o: k-shingles.cc k-shingles.hh
	$(CXX) $(CXXFLAGS) -c k-shingles.cc -o k-shingles.o

normalizeText.o: normalizeText.cc normalizeText.hh
	$(CXX) $(CXXFLAGS) -c normalizeText.cc -o normalizeText.o

jaccard.o: jaccard.cc jaccard.hh
	$(CXX) $(CXXFLAGS) -c jaccard.cc -o jaccard.o

minhash.o: minhash.cc minhash.hh
	$(CXX) $(CXXFLAGS) -c minhash.cc -o minhash.o

normalizeText2.o: normalizeText2.cc normalizeText2.hh
	$(CXX) $(CXXFLAGS) -c normalizeText2.cc -o normalizeText2.o

permutacions.o: permutacions.cc permutacions.hh
	$(CXX) $(CXXFLAGS) -c permutacions.cc -o permutacions.o

stopwords.o: stopwords.cc stopwords.hh
	$(CXX) $(CXXFLAGS) -c stopwords.cc -o stopwords.o

clean:
	rm -f $(OBJ) $(TARGET)
