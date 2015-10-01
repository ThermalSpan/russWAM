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



