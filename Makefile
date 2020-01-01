COMPILERFLAGS = -Wall
CPP = g++
CFLAGS = $(COMPILERFLAGS) 
LIBRARIES = -lpthread
DEPS = AirTrafficControl.h ControlTower.h RandomPlaneGenerator.h signals2.h

All: ATC_BIN

ATC_BIN: AirTrafficControl.o ControlTower.o RandomPlaneGenerator.o Signals2.o
	$(CPP) $(CFLAGS) -o $@ $^ $(LIBRARIES)
	rm *.o
clean:
	rm *.o
