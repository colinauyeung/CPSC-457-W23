SOURCES = containers.cpp ref_pointers_templates.cpp assorted.cpp
CPPC = g++
CPPFLAGS = -Wall -O2
TARGET = containers ref_pointers_templates assorted 

all: containers ref_pointers_templates assorted

%.o : %.c



containers: containers.cpp
	$(CPPC) $(CPPFLAGS) -o $@ containers.cpp

ref_pointers_templates: ref_pointers_templates.cpp
	$(CPPC) $(CPPFLAGS) -o $@ ref_pointers_templates.cpp

assorted: assorted.cpp
	$(CPPC) $(CPPFLAGS) -o $@ assorted.cpp


.PHONY: clean
clean:
	rm -f *~ *.o $(TARGET) 
