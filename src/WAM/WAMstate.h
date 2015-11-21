//
//  WAMstate.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 11/21/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//  

// This head file describes all the types necassary for:
//  - Using all four (non-code) memory regions

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


// The local stack contains environment frames and choice points
enum LocalType {Environment, ChoicePoint};
struct LocalFrame {
    LocalType 
};

// The Trail Stack is a doubly linked list of TrailFrames
struct TrailFrame {
    TrailFrame* prevFrame;
     
};
