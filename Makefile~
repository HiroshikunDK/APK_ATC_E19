COMPILERFLAGS = -Wall
CPP = g++
CFLAGS = $(COMPILERFLAGS) 
LIBRARIES = -l lthread
DEPS = AirTrafficControl.h ControlTower.h RandomPlaneGenerator.h signals2.h

All: ATCbuild

ATCbuild: AirTrafficControl.o ControlTower.o RandomPlaneGenerator.o Signals2.o % $(DEPS)
	$(CPP) $(CFLAGS) -o $@ $^ $(LIBRARIES)
	