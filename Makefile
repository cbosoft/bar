CXX = g++
CFLAGS = -g -pg -Wall -Wextra -Werror -std=c++17 -O2

RECIPE = \
				 obj/recipe/recipe.o \
				 obj/recipe/run.o \
				 obj/recipe/watch.o

RECIPES = \
					obj/recipes/recipes.o \
					obj/recipes/file.o \
					obj/recipes/watch.o

UTIL = \
			 obj/util/glob.o \
			 obj/util/notify.o \
			 obj/util/replace.o \
			 obj/util/run.o

HDR = $(shell ls src/**/*.hpp)
OBJ = $(RECIPE) $(RECIPES) $(UTIL)
LINK = -lpthread
DEFS =

.SECONDARY:

obj/%.o: src/%.cpp $(HDR)
	@echo -e "\u001b[33mASSEMBLING OBJECT $@\u001b[0m"
	@mkdir -p `dirname $@`
	@$(CXX) $(CFLAGS) $(DEFS) $< -c -o $@

obj/test/%.o: src/test/%.cpp $(HDR)
	@echo -e "\u001b[33mASSEMBLING OBJECT $@\u001b[0m"
	@mkdir -p `dirname $@`
	@$(CXX) $(CFLAGS) $(DEFS) $< -c -o $@


bar: obj/main.o $(OBJ) $(HDR)
	@echo -e "\u001b[34mLINKING OBJECTS TO EXECUTABLE $@\u001b[0m"
	@$(CXX) $(CFLAGS) $(DEFS) obj/main.o $(OBJ) -o $@ $(LINK)

install: bar
	cp bar /usr/bin/bar

clean:
	rm -rf obj bar tests
