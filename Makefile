# Created By Russell Bentley
# Copyright (c) 2015 Russell Wilhelm Bentley 
# Distributed under the MIT License

# Compiler Stuff
CC        = g++
CFLAGS    = -c -std=c++11 -stdlib=libc++ -Wall

# Directories
SRCDIR    = src
BUILDDIR  = build
TARGETDIR = bin
TSTDIR    = test
TEMPDIRS  = bin build build/Memory build/WAM build/test

# Files
SRCFILES  = $(shell find $(SRCDIR) -name *.cpp)
TSTFILES  = $(shell find $(TSTDIR) -name *.cpp)

SOBJFILES  = $(SRCFILES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
TOBJFILES  = $(TSTFILES:$(TSTDIR)/%.cpp=$(BUILDDIR)/test/%.o)

# Targets
$(TEMPDIRS):
	@echo  $@
	@mkdir $@

russWAMex       : $(SOBJFILES)
	$(CC) $^ -o $(TARGETDIR)/russWAMex

russWAMde       : $(TOBJFILES)
	$(CC) $^ -o -g bin/russWAMde

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	@echo "Compling: souce / executable"
	$(CC)  $(CFLAGS) $< -o $@

$(BUILDDIR)/test/%.o : $(TSTDIR)/%.cpp
	@echo "Compling: test"
	$(CC)  $(CFLAGS) $< -o $@

# Phony Commands
all: russWAMex

.PHONY: debug
debug:  $(TEMPDIRS)  russWAMde

.PHONY: clean
clean:
	rm -f -r build bin

.PHONY: test
test:	$(TEMPDIRS) $(SOBJFILES) $(TOBJFILES)
	$(CC) $(TOBJFILES)  build/Memory/PoolAllocator.o -o $(TARGETDIR)/test


