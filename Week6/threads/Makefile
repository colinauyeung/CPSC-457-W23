# SOURCES = containers.cpp ref_pointers_templates.cpp assorted.cpp
CPPC = g++
CPPFLAGS = -Wall -O2 -lpthread
TARGET =  basicthread workdivison

all: basicthread workdivison 

%.o : %.c


basicthread: basicthread.cpp
	$(CPPC) $(CPPFLAGS) -o $@ basicthread.cpp

workdivison: workdivison.cpp
	$(CPPC) $(CPPFLAGS) -o $@ workdivison.cpp



.PHONY: clean
clean:
	rm -f *~ *.o $(TARGET) 
