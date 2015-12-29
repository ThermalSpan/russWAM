# Created By Russell Bentley
# Copyright (c) 2015 Russell Wilhelm Bentley 
# Distributed under the MIT License

# Compiler Stuff
CC        	= g++
CFLAGS    	= -c -std=c++11 -stdlib=libc++ -Wall 
BISON 		= /usr/local/Cellar/bison/3.0.4/bin/bison
FLEX 		= flex

# Directories
TEMPDIRS  	= build bin build/Memory build/WAM build/test bin/test build/Loader

# File List/s
WAMFILES 	= FunctorTable put set get unify control core indexing run output cut choice
WAMHEADERS  = src/WAM/WAM.h src/WAM/FunctorTable.h
LOADFILES 	= gWAMparser gWAMsyntax
LOADHEADERS = $(LOADFILES:%=src/Loader/%.h)
GRAMFILE	= gWAMgrammar
FLEXFILES	= gWAMlexer 
EXEFILES 	= main utilities
EXEHEADERS  = src/utilities.h

# Derived Files Lists
WAMSRCFILES	= $(WAMFILES:%=src/WAM/%.cpp)
WAMOBJFILES	= $(WAMSRCFILES:src/%.cpp=build/%.o)

LOADSRC		= $(LOADFILES:%=src/Loader/%.cpp)
LOADOBJ  	= $(LOADSRC:src/%.cpp=build/%.o)

GRAMMARYS	= $(GRAMFILE:%=src/Loader/%.y)
GRAMSRC		= $(GRAMMARYS:src/Loader/%.y=build/Loader/%.c)
GRAMHED 	= $(GRAMSRC:%.c=%.h)
GRAMOBJ		= $(GRAMSRC:%.c=%.o)

FLEXLEX		= $(FLEXFILES:%=src/Loader/%.lex)
FLEXSRC 	= $(FLEXLEX:src/Loader/%.lex=build/Loader/%.c)
FLEXOBJ		= $(FLEXSRC:%.c=%.o)

EXESRCFILES = $(EXEFILES:%=src/%.cpp)
EXEOBJFILES = $(EXESRCFILES:src/%.cpp=build/%.o)

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
	$(CC) -g -c -x c++ -std=c++11 -stdlib=libc++ -Wno-deprecated-register -Wunneeded-internal-declaration -o $(GRAMOBJ) $(GRAMSRC) -MD 

$(FLEXOBJ) : $(FLEXSRC)
	$(CC) -g -c -x c++ -std=c++11 -stdlib=libc++ -Wno-deprecated-register -Wunneeded-internal-declaration -o $(FLEXOBJ) $(FLEXSRC) -MD

bin/russWAMex : $(GRAMOBJ) $(FLEXOBJ) $(LOADOBJ) $(WAMOBJFILES) $(EXEOBJFILES)
	$(CC) $^ -o bin/russWAMex

build/%.o : src/%.cpp
	$(CC) $(CFLAGS) -g $< -o $@

build/test/%.o : test/%.cpp
	$(CC) $(CFLAGS) -g $< -o $@

bin/test/% : build/test/%.o
	$(CC) $< $(WAMOBJFILES) -g -o $@

# Phony Command
.PHONY: style
style:
	astyle -A2 -s4 -xd -k1 -j $(EXESRCFILES) $(EXEHEADERS) $(LOADSRC) $(LOADHEADERS) $(WAMSRCFILES) $(WAMHEADERS)

.PHONY: install
install: bin/russWAMex
	cp bin/russWAMex Tests/russWAMex

.PHONY: clean
clean:
	rm -f -r build bin dirFile Tests/russWAMex Tests/*.wam Tests/russWAMex.dSYM *.orig
