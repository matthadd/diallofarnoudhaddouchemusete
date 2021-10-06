#compiler of the program
CXX := g++ 
CXXFLAGS := -g -Wall 

PROJNAME := state
SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))

.PHONY : all
all : clean $(PROJNAME) 

$(PROJNAME): $(OBJECTS)
	${CXX} $(OBJECTS) -o $(PROJNAME)

.PHONY : clean 
clean:
	rm -f $(PROJNAME) *.o *.h

.PHONY : build
build :
%.o : %.cpp
	${CXX} -c $(CXXFLAGS) -o $@ $<  
