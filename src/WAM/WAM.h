//
//  WAM.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 11/21/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//  

#pragma once

#include "types.h"
#include "FunctorTable.h"

class WAM {
public:

protected:
    DataCell* m_H;                          // The Heap Pointer
    DataCell* m_S;                          // The next term to be unified
    WAMword* m_P;                           // The next Instruction to be run
    WAMword* m_CP;                          // The continuation instruction
    WAMword* m_L;                           // L for label: the next clause to try
    WAMword* m_TR;                          // Trail point, 
    // HB - the backtracking point in the heap, is a getMethod
    Mode m_Mode;                            // READ or WRITE?
    int m_arity;                            // Arity of local functor, called num_of_args in tutorial
    int m_functorId;                        // The functor id of last call or execute, used in the switch statements

    // Data areas
    DataCell* m_Heap;                       // The base of the HEAP, an array of DataCells
    DataCell** m_Trail                      // The base of the trail, and array of DataCell addresses 
    addressStack* m_PDL;                    // Stack of data cells used for unification
    FunctorTable* m_functorTable;           // A data struture used to identify functors
    EnvFrame* m_E;                          // The top of the local frame stack
    ChoiceFrame* m_B;

public:
    WAM ();
    ~WAM ();

protected:
    // Put instructions
    void put_variable (RegType t, int regId, int argRegId);
    void put_value (RegType t, int regId, int argRegId);
    void put_unsafe_value (int regId, int argRegId);
    void put_structure (int functorId, int argRegId);
    void put_list (int argRegId);
    void put_constant (int functorId, int argRegId);

    // Get instructions
    void get_variable (RegType t, int regId, int argRegId);
    void get_value (RegType t, int regId, int argRegId);
    void get_structure (int functorId, int argRegId);
    void get_list (int argRegId);
    void get_constant (int functorId, int argRegId);

    // Set instructions
    void set_variable (RegType t, int regId);
    void set_value (RegType t, int regId);
    void set_local_value (RegType t, int regId);
    void set_constant (int functorId);
    void set_void (int n);

    // Unify intructions 
    void unify_variable (RegType t, int regId);
    void unify_value (RegType t, int regId);
    void unify_local_value (RegType t, int regId);
    void unify_constant (int functorId);
    void unify_void (int n);
    bool unify (DataCell* cell1, DataCell* cell2);

    // Control instructions
    void allocate (int N);
    void deallocate ();
    void call (int functorId);
    void execute (int functorId);
    void proceed ();
    
    // Choice instructions
    void try_me_else (int labelId);
    void retry_me_else (int labelId);
    void trust_me ();
    void try_ (int labelId);
    void retry (int labelId);
    void trust (int labelId);
    
    // Indexing instructions
    void switch_on_term (int V, int C, int L, int S);
    void switch_on_constant ();
    void switch_on_structure ();    

    // Cut instructions
    
    // Support instructions
    void backtrack ();
    DataCell* deref (DataCell* address);
    void bind (DataCell* cell1, DataCell* cell2);
    void trail (DataCell* address);
    void unwind_trail (TrailFrame* oldTr, TrailFrame* curTr);

    void panic (string message);
    DataCell* getHB ();                                         // HB, would normally be a "register"

    // DataCell manipulation
    DataCell* getLocalReg (int regId);
    DataCell* getGlobalReg (int regId);
    DataCell* getRegister (RegType t, int regId);
    bool isStackCell (DataCell* cell);
    bool isHeapCell (DataCell* cell);
    bool unboundHeap (DataCell* cell);
    bool unboundStack (DataCell* cell);
};
