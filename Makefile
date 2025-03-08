# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

# Archivos fuente y objetos
SRC = main.cc k-shingles.cc normalizeText.cc jaccard.cc minhash.cc
OBJ = $(SRC:.cc=.o)
DEPS = k-shingles.hh normalizeText.hh jaccard.hh minhash.hh

# Nombre del ejecutable
TARGET = ProjecteA

# Regla principal
all: $(TARGET)

# Compilar el ejecutable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar archivos .cc en .o
%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos compilados
clean:
	rm -f $(OBJ) $(TARGET)
