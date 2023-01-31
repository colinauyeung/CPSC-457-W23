SOURCES = files.cpp 
CPPC = g++
CPPFLAGS = -Wall -O2
TARGET = files 

all: files 

files: files.cpp
	$(CPPC) $(CPPFLAGS) -o $@ files.cpp



.PHONY: clean
clean:
	rm -f *~ *.o $(TARGET) 
