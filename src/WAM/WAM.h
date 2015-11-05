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
#include "Types.h"
#include "Heap.h"
#include "FunctorTable.h"

#define ARG_REG_COUNT 10
#define MEMSIZE 8128

using namespace std;

class WAM {
public:
    WAM (FunctorTable* functorTable);
  
    ~WAM ();
    
    // WAM Instructions
    // put 
    void put_structure (int functorId, int regId);

    // set
    void set_variable (int regId);

    void set_value (int regId);
    
    // get
    RtnCode get_structure (int functorId, int regId);

    //Unify 
    void unify_variable (int regId);

    void unify_value (int regId);

protected:
    // Protected Functions
    void bind (DataCell* a, DataCell* b);

    DataCell* deref (DataCell* cell);

	RtnCode unify (DataCell* a, DataCell* b);

    void setSreg (DataCell* cell);

   // Protected Variables
    FunctorTable* m_FunctorTable;

    DataCell* m_argRegisters;
 
    Heap* m_heap;

    AddrStack* m_UnifStack;

    DataCell* m_Hindex;

    Mode m_mode;

    // The next sub-term to be matched
    DataCell* m_Sreg;
};


