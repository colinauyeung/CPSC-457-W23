SOURCES = groceries.cpp
CPPC = g++
CPPFLAGS = -Wall -O2
TARGET = groceries

all: $(TARGET)

%.o : %.c



$(TARGET): $(SOURCES)
	$(CPPC) $(CPPFLAGS) -o $@ $(SOURCES)


.PHONY: clean
clean:
	rm -f *~ *.o $(TARGET) 
