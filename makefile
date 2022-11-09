#CPPFLAGS = -w -std=c++11 -O3 -I include
#LNKFLAGS1 = -pg -w -std=c++11 -O3 -I include

CPPFLAGS = -std=c++11 -m64 -I include
LNKFLAGS1 = -std=c++11 -m64 -I include
 
COMP = g++

TARGET = ArvoreGeradora.exe

OBJ = AndersonV4.o Grafo.o main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(COMP) $(LNKFLAGS1) $(OBJ) -o $@

AndersonV4.o: src/AndersonV4.cpp
	$(COMP) $(CPPFLAGS) -c $< 

Grafo.o: src/Grafo.cpp
	$(COMP) $(CPPFLAGS) -c $< 

main.o: main.cpp
	$(COMP) $(CPPFLAGS) -c $<
	
	

clean:
	rm -f $(OBJ) $(TARGET)	
