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

#define HEAPSIZE 9000
#define ARGREGCOUNT 30
#define TRAILSIZE 100

class WAM {
protected:
    //
    // State Registers
    //
    DataCell* m_H;                          // The Heap Pointer
    DataCell* m_HB;                         // The Backtracking point on the heap
    DataCell* m_S;                          // The next term to be unified
    WAMword* m_P;                           // The next Instruction to be run
    WAMword* m_CP;                          // The continuation instruction
    ChoiceFrame* m_B0;                      // The cut pointer
    DataCell** m_TR;                          // Trail point,
    Mode m_Mode;                            // READ or WRITE?
    int m_arity;                            // Arity of local functor, called num_of_args in tutorial
    int m_functorId;                        // The functor id of last call or execute, used in the switch statements

    //
    // Data areas
    //
    DataCell* m_Heap;                       // The base of the HEAP, an array of DataCells
    DataCell* m_GlobalArgRegisters;         // An array of datacells to serve as global registers
    DataCell** m_Trail;                     // The base of the trail, and array of dataCell addresses
    addressStack* m_PDL;                    // Stack of data cells used for unification
    FunctorTable* m_functorTable;           // A data struture used to identify functors
    EnvFrame* m_E;                          // The top of the local frame stack
    ChoiceFrame* m_B;

    //
    // Extras
    //
    WAMword* m_endWord;                    // A null word to use as first m_CP

public:
    //
    // Public Methods
    //
    WAM (FunctorTable* functorTable);
    ~WAM ();

    bool run (string* functor, int arity);
    bool runBacktrack ();
    void printResultArg (int reg);
    void printCell (DataCell* cell);


protected:
    //
    // Private Methods
    //

    // Put instructions
    void put_variable (RegType t, int regId, int argRegId);
    void put_value (RegType t, int regId, int argRegId);
    void put_unsafe_value (int regId, int argRegId);
    void put_structure (int functorId, int argRegId);
    void put_list (int argRegId);
    void put_constant (int functorId, int argRegId);
    void put_void (int argRegId);

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
    void trust_me_else_fail ();
    void try_ (int labelId);
    void retry (int labelId);
    void trust (int labelId);

    // Indexing instructions
    void switch_on_term (int V, int C, int L, int S);
    void switch_on_constant ();
    void switch_on_structure ();

    // Cut instructions
    void neck_cut ();
    void get_level (int regId);
    void cut (int regId);

    // Output Instructions
    long HeapCellId (DataCell* pointer);
    void printHeap ();
    void recurPrint (DataCell* cell);
    void printArgRegisters ();
    DataCell* strDeref (DataCell* cell);


    // Support instructions
    void backtrack ();
    DataCell* deref (DataCell* address);
    void bind (DataCell* cell1, DataCell* cell2);
    void trail (DataCell* address);
    void unwind_trail (DataCell** oldTr, DataCell** curTr);

    void panic (string message);
    bool executeInstr (WAMword* word);

    // DataCell manipulation
    DataCell* getLocalReg (int regId);
    DataCell* getGlobalReg (int regId);
    DataCell* getRegister (RegType t, int regId);
    bool isGlobalCell (DataCell* cell);
    bool isStackCell (DataCell* cell);
    bool isHeapCell (DataCell* cell);
    bool unboundHeap (DataCell* cell);
    bool unboundStack (DataCell* cell);

    // Debug Print stuff
    string tag2str (Tag t);
};
