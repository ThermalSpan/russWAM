//
//  Types.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/15/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//  

#pragma once

#include "../stdafx.h"

// The DataCell is the fundemenetal type maniupulated in the WAM
enum Tag {REF, STR};

enum CellType {VAL, FUN};

struct DataCell {
    CellType type;
    union {
        Tag tag;
        int functorId;
    };
    union {
        int arity;
        DataCell* ref;
    };
};

// Error Codes used for return values
enum RtnCode {
    SUCCESS,                // All is well! 
    UNKNOWN_OP,             // In driver loop, default case is reached
    TERMINATED,             // a terminate instruction was found.
    GET_STRUCT_FAIL,        // get_structure found a non REF, or STR didn't point to f/n
    UNIFY_FAIL              // unify (a1, a2) failed to complete
};

// The WAM has some modal instructions.
enum Mode {READ, WRITE};

// Some operations specify the register type
enum RegType {X = 0, Y = 1};

enum OpCode {
    OC_cut_variable,
    OC_put_variable,
    OC_put_value,
    OC_put_unsafevalue,
    OC_put_structure,
    OC_put_list,
    OC_put_constant,
    OC_set_variable,
    OC_set_value,
    OC_set_localvalue,
    OC_set_constant,
    OC_set_void,
    OC_allocate,
    OC_deallocate,
    OC_call,
    OC_execute,
    OC_proceed,
    OC_switch_on_term,
    OC_switch_on_constant,
    OC_switch_on_structure,
    OC_get_variable,
    OC_get_value,
    OC_get_structure,
    OC_get_list,
    OC_get_constant,
    OC_unify_variable,
    OC_unify_value,
    OC_unify_localvalue,
    OC_unify_constant,
    OC_unify_void,
    OC_try_me_else,
    OC_retry_me_else,
    OC_trust_me,
    OC_try,
    OC_retry,
    OC_trust,
    OC_neck_cut,
    OC_get_level,
    OC_cut,
	OC_printHeap,
	OC_printArgRegisters,
	OC_printResultArg,
    OC_printHeapCell,
    OC_unifyHeapCells,
	OC_write,
    OC_terminate
};

// This structure represents one WAM intruction
struct WAMword {
    OpCode op;
	int a;
	int b;
	int c;
};

// This is what the STACK uses
struct EnvFrame {
    WAMword* CE;
    WAMword* CP;
    std::vector <DataCell> registers;

    EnvFrame () : registers () {
        CE = nullptr;
        CP = nullptr;
    }

    EnvFrame(WAMword* _CE, WAMword* _CP, int N) : registers (N) {
        CE = _CE;
        CP = _CP;
    }
};


// Useful typedefs
typedef std::vector <std::string> StrVec;
typedef std::stack <DataCell*> AddrStack;


