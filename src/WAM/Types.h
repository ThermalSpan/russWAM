//
//  types.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 11/21/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//  

#pragma once

#include <stdlib.h>
#include <stack>
#include <vector>
#include "opcode.h"

// The WAM has some modal instructions.
enum Mode {READ, WRITE};

// Argument Registers can either be global or local (on the locals stack)
enum RegType {GLOBAL, LOCAL};

// The DataCell is the fundemenetal type maniupulated in the WAM
enum Tag {REF, STR, FUN, LIS, CON};

struct DataCell {
    Tag tag;
    union {
        DataCell* ref;
        int functorId;
    };
};

// This structure represents one WAM instruction
struct WAMword {
    OpCode op;
    int a;
    int b;
    int c;
};

// The Trail Stack is a doubly linked list of TrailFrames
struct TrailFrame {
    TrailFrame* prevFrame;
     
};


// Environment frames are stuck together like a list,
struct EnvFrame {
    EnvFrame* prev;
    WAMword* contPoint;
    std::vector <DataCell> LocalRegs;

    EnvFrame (int N, WAMword* CP, EnvFrame* frame) : LocalRegs(N) {
        contPoint = CP;
        prev = frame; 
    }
};

// Contain all the information to undo a choice, forms a list
struct ChoiceFrame {
    int arity;
    std::vector <DataCell> GlobalRegs;
    EnvFrame* E;
    WAMword* CP;
    ChoiceFrame* prevChoice;
    WAMword* nextClause;
    TrailFrame* TR;
    DataCell* H;
    ChoiceFrame* B0;                // Where to go when cut, often refered to B0

    ChoiceFrame (int n, ChoiceFrame* prev) : GlobalRegs (n) {
        prevChoice = prev;
    }    
};

// Some useful typedefs
typedef std::stack <DataCell*> addressStack;
typedef std::vector <DataCell> dataCellVector;

