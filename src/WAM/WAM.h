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
  
    virtual ~WAM ();
    
    // WAM Instructions
    // put 
    void put_structure (int functorId, int regId);
    
    void put_variable (int regType, int reg1, int reg2);

    void put_value (int regType, int reg);

    // set
    void set_variable (int regId);

    void set_value (int regId);
    
    // get
    void get_variable (int regType, int reg1, int reg2);

    void get_value (int regType, int reg1, int reg2);

    RtnCode get_structure (int functorId, int regId);

    //Unify 
    void unify_variable (int regId);

    void unify_value (int regId);

protected:
    // Protected Functions
    void bind (DataCell* a, DataCell* b);

    DataCell* deref (DataCell* cell);

    RtnCode unify (DataCell* a, DataCell* b);

    // These methods are virtual so I can plug in debug statements
    virtual void setSreg (DataCell* cell);

    virtual void setHindex (DataCell* cell);

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


