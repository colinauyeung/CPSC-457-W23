SOURCES = files.cpp fork_basic.cpp fork_exec.cpp fork_pipe.cpp system.cpp
CPPC = g++
CPPFLAGS = -Wall -O2
TARGET = files fork_basic fork_exec system fork_pipe

all: files fork_basic fork_exec system fork_pipe

files: files.cpp
	$(CPPC) $(CPPFLAGS) -o $@ files.cpp

fork_basic: fork_basic.cpp
	$(CPPC) $(CPPFLAGS) -o $@ fork_basic.cpp

fork_exec: fork_exec.cpp
	$(CPPC) $(CPPFLAGS) -o $@ fork_exec.cpp

fork_pipe: fork_pipe.cpp
	$(CPPC) $(CPPFLAGS) -o $@ fork_pipe.cpp

system: system.cpp
	$(CPPC) $(CPPFLAGS) -o $@ system.cpp


.PHONY: clean
clean:
	rm -f *~ *.o $(TARGET) 
