#compiler of the program
CXX := gcc
#compiler flags :
CXXFLAGS := -g -Wall
INCLUDES := -I

PROGRAMS  := prog
OBJECTS := *.o

$(PROGRAMS) : $(OBJECTS)
	$(CXX) $(inputs) -o $(output) 

%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(INCLUDES) -cpp $(input)  -o $(output)

$(phony clean):
	rm -f $(PROGRAMS) *.o *.h
