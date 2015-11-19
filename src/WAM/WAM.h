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
    WAM (FunctorTable* functorTable, StrVec* stringTable, WAMword* code, int size);
  
    virtual ~WAM ();

    void run ();
    
    // WAM Instructions
    // Put 
    void put_structure (int functorId, int regId);
    
    void put_variable (int regType, int regId, int argRegId);

    void put_value (int regType, int regId);

    // Set
    void set_variable (int regId);

    void set_value (int regId);
    
    // Get
    void get_variable (int regType, int regId, int argRegId);

    void get_value (int regType, int regId, int argRegId);

    RtnCode get_structure (int functorId, int regId);

    // Unify 
    void unify_variable (int regId);

    void unify_value (int regId);

    // Control
    void call (int functorId);

    void proceed ();

    void allocate (int N);

    void deallocate ();

    // Debug Stuff
    void printHeap ();

    void printArgRegisters ();

    void printResultArg (int reg);

    void printHeapCell (int i);

    void unifyHeapCells (int a, int b);

    DataCell* getBase ();

    void printCell (DataCell* cell);

protected:
    // Protected Functions
    void bind (DataCell* a, DataCell* b);

    DataCell* deref (DataCell* cell);

    RtnCode unify (DataCell* a, DataCell* b);

    DataCell* getEnvReg (int regId);

    RtnCode ExecuteInstruction (WAMword* instr);

    void incrPreg ();

    void setSreg (DataCell* cell);

    void setHindex (DataCell* cell);

    // Debug Stuff
    DataCell* strDeref (DataCell* cell);

    void recurPrint (DataCell* cell);
    
    long ptrToHeapCell (DataCell* pointer);


   // Protected Variables
    FunctorTable* m_FunctorTable;

    DataCell* m_argRegisters;
 
    Heap* m_heap;

    AddrStack* m_UnifStack;

    EnvStack* m_EnvStack;

    DataCell* m_Hindex;

    Mode m_mode;

    StrVec* m_StringTable;
    
    // Core Array;
    WAMword* m_Code;

    int m_size;

    // Next instruction
    WAMword* m_Preg;
    
    // Continuation instruction
    WAMword* m_CPreg;

    // The next sub-term to be matched
    DataCell* m_Sreg;

    int m_maxHindex;

};


