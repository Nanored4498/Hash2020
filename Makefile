GCCFLAGS = -Wall -Wextra -O3 #-std=c++17 #-ansi -pedantic -std=c11 -g
EXEC = victorMONTEcarloMONTEblockchain
LIBS = 
OLIBS=$(patsubst %,%.o,$(LIBS))
HLIBS=$(patsubst %,%.h,$(LIBS))
CC = g++

all: $(EXEC)

#EXEC = % with this, so %.o works
$(EXEC) : % : $(OLIBS) %.o 
	$(CC) $(GCCFLAGS) -o $@ $^

# needed otherwise a built in rule (and deps?...) is called that
# is not triggered by cantstop.h change
main.o : main.cpp $(HLIBS)
	$(CC) $(GCCFLAGS) -c $<

.o : main.cpp $(HLIBS)
	$(CC) $(GCCFLAGS) -c $<

%.o: %.cpp %.h $(HLIBS)
	$(CC) $(GCCFLAGS) -c $<

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f *.gch

nemo-%:
	g++ -Wall -Wextra -std=c++11 nemo.cpp -o nemo
	./nemo < data/$(subst nemo-,,$@).txt > output-$@
	head output-$@
