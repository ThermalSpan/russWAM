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
    SUCCESS,               // All is well! 
    GET_STRUCT_FAIL,       // get_structure found a non REF, or STR didn't point to f/n
    UNIFY_FAIL             // unify (a1, a2) failed to complete
};


// The WAM has some modal instructions.
enum Mode {READ, WRITE};




