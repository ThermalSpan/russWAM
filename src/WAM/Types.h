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

// The local stack contains environment frames and choice points
enum LocalType {ENVIRON, CHOICEP};
struct LocalFrame {
    LocalType type;
};

// The Trail Stack is a doubly linked list of TrailFrames
struct TrailFrame {
    TrailFrame* prevFrame;
     
};

// We can now describe the state of the WAM
struct MemoryRegisters {
    WAMword* P;                 // Program Counter
    WAMword* CP;                // Continuation Pointer
    LocalFrame* CurEnv;         // Current Environment Pointer
    LocalFrame* B;              // Most Recent Choice Point
    DataCell* H;                // Top of the Heap
    DataCell* HB;               // Heap Backtrack point
};

// Some useful typedefs
typedef std::stack <DataCell*> addressStack;

