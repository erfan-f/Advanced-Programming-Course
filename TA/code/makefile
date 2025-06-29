CXX = g++
CXXFLAGS = -std=c++20

OBJ = main.o ioHandler.o tree.o node.o orderedSet.o

MK: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o MK.out

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) MK.out