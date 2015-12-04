//
//  types.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 11/21/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//  

#pragma once

#include "opcode.h"
#include <stack>
#include <vector>

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

struct ChoiceFrame {
    int arity;
    std::vector <DataCell> GlobalRegs;
    EnvFrame* contEnv;
    WAMword* contPoint;
    ChoiceFrame* prevChoice;
    WAMword* nextClause;
    TrailFrame* trailPoint;
    DataCell* heapPoint;
    ChoiceFrame* cutPointer;                // Where to go when cut, often refered to B0

    
};

// Some useful typedefs
typedef std::stack <DataCell*> addressStack;
typedef std::vector <DataCell> dataCellVector;

