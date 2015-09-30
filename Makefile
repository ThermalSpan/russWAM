# Created By Russell Bentley
# Copyright (c) 2015 Russell Wilhelm Bentley 
# Distributed under the MIT License

# Compiler Stuff
CC        = g++
CFLAGS    = -c -std=c++11 -stdlib=libc++ -Wall

# Directories
TEMPDIRS  = build bin build/Memory build/WAM build/test

# Files
WAMFILES = Engine Heap
WAMSRCFILES = $(WAMFILES:%=src/WAM/%.cpp)
WAMOBJFILES = $(WAMSRCFILES:src/%.cpp=build/%.o)

EXEFILES = main
EXESRCFILES = $(EXEFILES:%=src/%.cpp)
EXEOBJFILES = $(EXESRCFILES:src/%.cpp=build/%.o)

# Targets
all: dirFile bin/russWAMex

dirFile:
	for dir in $(TEMPDIRS); do \
		mkdir -p $$dir ; \
	done
	@touch dirFile

bin/russWAMex       : $(WAMOBJFILES) $(EXEOBJFILES)
	$(CC) $^ -o bin/russWAMex

build/%.o : src/%.cpp
	$(CC)  $(CFLAGS) $< -o $@

# Phony Commands

.PHONY: clean
clean:
	rm -f -r build bin dirFile
