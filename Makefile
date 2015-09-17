# Created By Russell Bentley
# Copyright 2015
# Distributed under the MIT License

# Compiler Stuff
CC = g++
CFLAGS = -c -std=c++11 -stdlib=libc++ -Wall

# Directories
SRCDIR = src
BUILDDIR = build
TARGETDIR = bin

# Files
SRCFILES = $(shell find $(SRCDIR) -name *.cpp)
OBJFILES = $(SRCFILES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)


# Targets

russWAMex : $(OBJFILES)
	$(CC) $^ -o $(TARGETDIR)/russWAMex

russWAMde : $(OBJFILES)
	$(CC) $^ -o -g bin/russWAMde

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC)  $(CFLAGS) $< -o $@

all: russWAMex

clean:
	rm build/*.o build/*/*.o bin/*



