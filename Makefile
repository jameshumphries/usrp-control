#Needs this to find "*.h" files needed
CFLAGS=-O2 -g -Wall -W $(shell pkg-config --cflags uhd)
#Needs this to find libraries that .h files point to
LDLIBS+=$(shell pkg-config --libs uhd) -lpthread -lm
CC=g++
PROGNAME=usrp-control
#make print-VARIABLE
print-%  : ; @echo $* = $($*)

all: usrp-control

usrp-control: main.cpp
	$(CC) -g -o usrp-control main.cpp $(CFLAGS) $(LDLIBS) -lboost_system -lboost_program_options

clean:
	rm -f *.o usrp-control
