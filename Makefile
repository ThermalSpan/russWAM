# Created By Russell Bentley
# Copyright (c) 2015 Russell Wilhelm Bentley 
# Distributed under the MIT License

# Compiler Stuff
CC        	= g++
CFLAGS    	= -c -std=c++11 -stdlib=libc++ -Wall -Wno-deprecated-register
BISON 		= /usr/local/Cellar/bison/3.0.4/bin/bison
FLEX 		= flex

# Directories
TEMPDIRS  	= build bin build/Memory build/WAM build/test bin/test build/Loader

# File List/s
WAMFILES 	= Heap Stack WAMdebug core unify put set FunctorTable
LOADFILES 	= rWAMparser
GRAMFILE 	= rWAMgrammar
FLEXFILES   = rWAMscanner
EXEFILES 	= main
TSTFILES 	= QueryTerms Deref

# Derived Files Lists
WAMSRCFILES = $(WAMFILES:%=src/WAM/%.cpp)
WAMOBJFILES = $(WAMSRCFILES:src/%.cpp=build/%.o)

LOADSRC		= $(LOADFILES:%=src/Loader/%.cpp)
LOADOBJ  	= $(LOADSRC:src/%.cpp=build/%.o)

GRAMMARYS   = $(GRAMFILE:%=src/Loader/%.y)
GRAMSRC		= $(GRAMMARYS:src/Loader/%.y=build/Loader/%.c)
GRAMHED 	= $(GRAMSRC:%.c=%.h)
GRAMOBJ		= $(GRAMSRC:%.c=%.o)

FLEXLEX     = $(FLEXFILES:%=src/Loader/%.lex)
FLEXSRC 	= $(FLEXLEX:src/Loader/%.lex=build/Loader/%.c)
FLEXOBJ		= $(FLEXSRC:%.c=%.o)

EXESRCFILES = $(EXEFILES:%=src/%.cpp)
EXEOBJFILES = $(EXESRCFILES:src/%.cpp=build/%.o)

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

$(GRAMSRC) $(GRAMHED) : $(GRAMMARYS)
	$(BISON) -d -o $(GRAMSRC) $(GRAMMARYS)

$(FLEXSRC) : $(GRAMHED)
	$(FLEX) --bison-bridge -o $(FLEXSRC) $(FLEXLEX)

$(GRAMOBJ) : $(GRAMSRC) 
	$(CC) -g -c -x c++ $(CFLAGS) -o $(GRAMOBJ) $(GRAMSRC) -MD 

$(FLEXOBJ) : $(FLEXSRC)
	$(CC) -g -c -x c++ $(CFLAGS) -o $(FLEXOBJ) $(FLEXSRC) -MD

bin/russWAMex : $(GRAMOBJ) $(FLEXOBJ) $(LOADOBJ) $(WAMOBJFILES) $(EXEOBJFILES)
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
