//
//  Engine.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/12/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#pragma once

#include "../stdafx.h"
#include "types.h"
#include "Heap.h"
#include "Stack.h"

#define ARG_REG_COUNT 10
#define MEMSIZE 8128

using namespace std;

typedef vector <string> StrVec;

class WAM {
public:
    WAM ();
  
    ~WAM ();

    DataCell* deref (DataCell* cell);

    void put_structure (int functorId, int arity, int regId);

    void set_variable (int regId);

    void set_value (int regId);

    void bind (DataCell* a, DataCell* b);

    RtnCode get_structure (int functorId, int arity, int regId);

    void unify_variable (int regId);

    void unify_value (int regId);

	RtnCode unify (DataCell* a, DataCell* b);
    
    void addString (int i, string s);

    void printHeap ();

	void printArgRegisters ();

    DataCell* getBase ();

    string getFunctor (int functorId);

protected:

    StrVec m_functortable;

    DataCell* m_argRegisters;
 
    Heap* m_heap;

    Stack* m_UnifStack;

    DataCell* m_Hindex;

    Mode m_mode;

    DataCell* m_Sreg;
};


