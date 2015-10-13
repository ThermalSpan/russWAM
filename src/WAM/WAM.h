//
//  WAM.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/15/15.
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
    
    // WAM Instructions
    // put 
    void put_structure (int functorId, int arity, int regId);

    // set
    void set_variable (int regId);

    void set_value (int regId);
    
    // get
    RtnCode get_structure (int functorId, int arity, int regId);

    //Unify 
    void unify_variable (int regId);

    void unify_value (int regId);

    // Utility Functions
    void addString (int i, string s);

    string getFunctor (int functorId);

protected:
    // Protected Functions
    void bind (DataCell* a, DataCell* b);

    DataCell* deref (DataCell* cell);

	RtnCode unify (DataCell* a, DataCell* b);

   // Protected Variables
    StrVec m_functortable;

    DataCell* m_argRegisters;
 
    Heap* m_heap;

    Stack* m_UnifStack;

    DataCell* m_Hindex;

    Mode m_mode;

    DataCell* m_Sreg;
};


