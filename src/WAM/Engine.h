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

#define ARG_REG_COUNT 10
#define MEMSIZE 8128

using namespace std;

typedef vector <string> StrVec;

class WAM {
public:
    WAM ();
  
    ~WAM ();

    void put_structure (int functorId, int arity, int regId);

    void set_variable (int regId);

    void set_value (int regId);

    int deref (int index);

	void unify (int a, int b);
    
    void addString (int i, string s);

    void printHeap ();

	void printArgRegisters ();

protected:

    StrVec m_functortable;

    DataCell* m_argRegisters;
 
    Heap* m_heap;

    int m_Hindex;
};


