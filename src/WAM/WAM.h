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
    DataCell* m_H;
    DataCell* m_S;
    WAMword* m_P;
    WAMword* m_CP;
    Mode m_Mode;

    // Data areas
    DataCell* m_Heap;
    addressStack* m_PDL;
    FunctorTable* m_functorTable;

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
    
    // Choice instructions
    
    // Indexing instructions
    
    // Cut instructions
    
    // Support instructions
    void backtrack ();
    DataCell* deref (DataCell* address);
    void bind (DataCell* cell1, DataCell* cell2);
    void trail (DataCell* address);
    void unwind_trail (DataCell* cell1, DataCell* cell2);

    // DataCell manipulation
    DataCell* getLocalReg (int regId);
    DataCell* getGlobalReg (int regId);
    DataCell* getRegister (RegType t, int regId);
    bool isStackCell (DataCell* cell);
    bool isHeapCell (DataCell* cell);
    bool unboundHeap (DataCell* cell);
    bool unboundStack (DataCell* cell);
};
