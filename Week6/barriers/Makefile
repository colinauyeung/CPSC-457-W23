CPPC = g++
CPPFLAGS = -Wall -O2 -lpthread
TARGET = barriers


all: barriers barriersimple atomicandprinting


barriers: barriers.cpp
	$(CPPC) $(CPPFLAGS) -o $@ barriers.cpp

barriersimple: barriersimple.cpp
	$(CPPC) $(CPPFLAGS) -o $@ barriersimple.cpp

atomicandprinting: atomicandprinting.cpp
	$(CPPC) $(CPPFLAGS) -o $@ atomicandprinting.cpp