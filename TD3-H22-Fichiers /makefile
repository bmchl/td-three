# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
# https://cs.colby.edu/maxwell/courses/tutorials/maketutor/
CXX=g++
RM=rm -f

# https://bytes.usc.edu/cs104/wiki/gcc/
# https://stackoverflow.com/questions/5088460/flags-to-enable-thorough-and-verbose-g-warnings
# https://github.com/Barro/compiler-warnings/blob/master/gcc/warnings-gcc-8.txt
# -fno-exceptions -fsanitize=address -fshort-enums -fpack-struct
# -funsigned-bitfields -funsigned-char
# -Wconversion -Werror -Wimplicit -Winline -Wmissing-declarations -Wno-unused 
# -Wold-style-cast
CXXFLAGS=-ansi \
	--coverage \
	-g \
	-pedantic \
	-std=c++20 -Wall

# CXXFLAGS=-std=c++20


LDFLAGS=
IDIR=include

SRCS=td2.cpp bibliotheque_cours.cpp verification_allocation.cpp
DEPS=bibliotheque_cours.hpp structures.hpp verification_allocation.hpp
OBJS=$(subst .cpp,.o,$(SRCS))
# EXEC=Debug/td2
EXEC=td2.out

PROJECTNAME=TD2
ZIPNAME=$(PROJECTNAME)_2121489_2141493.zip

all: run

$(EXEC): $(SRCS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -I$(IDIR) -o $@ $^

build: $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean:
	$(RM) $(OBJS) $(EXEC) $(ZIPNAME) *.gch *.gcda *.gcno

zip: $(SRCS)
	zip $(ZIPNAME) $(SRCS)