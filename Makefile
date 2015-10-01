# Created By Russell Bentley
# Copyright (c) 2015 Russell Wilhelm Bentley 
# Distributed under the MIT License

# Compiler Stuff
CC        = g++
CFLAGS    = -c -std=c++11 -stdlib=libc++ -Wall

# Directories
TEMPDIRS  = build bin build/Memory build/WAM build/test bin/test

# Files
WAMFILES = Engine Heap unify Stack
WAMSRCFILES = $(WAMFILES:%=src/WAM/%.cpp)
WAMOBJFILES = $(WAMSRCFILES:src/%.cpp=build/%.o)

EXEFILES = main
EXESRCFILES = $(EXEFILES:%=src/%.cpp)
EXEOBJFILES = $(EXESRCFILES:src/%.cpp=build/%.o)

TSTFILES = QueryTerms Deref
TSTSRCFILES = $(TSTFILES:%=test/%.cpp)
TSTOBJFILES = $(TSTSRCFILES:test/%.cpp=build/test/%.o)
TSTEXEFILES = $(TSTSRCFILES:test/%.cpp=bin/test/%)

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
	$(CC) $(CFLAGS) $< -o $@

build/test/%.o : test/%.cpp
	$(CC) $(CFLAGS) $< -o $@

bin/test/% : build/test/%.o
	$(CC) $< $(WAMOBJFILES) -o $@

# Phony Commands

.PHONY: t
t:	
	@echo $(TSTOBJFILES)
	@echo $(TSTEXEFILES)

.PHONY: test
test: dirFile $(WAMOBJFILES) $(TSTEXEFILES)

.PHONY: clean
clean:
	rm -f -r build bin dirFile
