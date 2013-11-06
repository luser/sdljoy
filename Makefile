CXXFLAGS=`sdl-config --cflags` -Wall -Werror
LIBS=`sdl-config --libs`

sdljoy: sdljoy.o
	$(CXX) -o $@ $< $(LIBS)
