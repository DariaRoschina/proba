CXX=c++
CXX_FLAGS=
LD=c++
LDFLAGS=
RMRF=rm -rf

ICE_HOME=/usr
SLICE2CPP=${ICE_HOME}/bin/slice2cpp
ICE_INC=${ICE_HOME}/include
ICE_LIB=${ICE_HOME}/lib
ICE_VER=3.5.1

OBJS=Printer.o \
     Server.o \
     client.o 

all: server client

Printer.h Printer.cpp: Printer.ice
	$(SLICE2CPP) -I/usr/share/Ice-$(ICE_VER)/slice $^

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c -I. -I$(ICE_INC) $<


client.cpp: Printer.h 
Server.cpp: Printer.h 

server: Server.o Printer.o 
	$(LD) $^ -Wl,-rpath=$(ICE_LIB) -L$(ICE_LIB) -lIce -lIceUtil -lpthread -o $@

client: client.o Printer.o 
	$(LD) $^ -Wl,-rpath=$(ICE_LIB) -L$(ICE_LIB) -lIce -lIceUtil -lpthread -o $@

clean:
	$(RMRF) $(OBJS) *~ server client Printer.h Printer.cpp */*~
