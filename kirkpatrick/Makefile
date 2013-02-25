CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,$(CPP_FILES))
FLAGS := -lGL -lGLU -lglut

obj/%.o : src/%.cpp
	g++ $(CXXFLAGS) $(FLAGS) -c -o $@ $<

kirkpatrick.bin : $(OBJ_FILES) 
	g++  $(CXXFLAGS) $(FLAGS) -lpthread $^ -o $@

clean:
	rm -rf obj/*.o kirkpatrick.bin 
