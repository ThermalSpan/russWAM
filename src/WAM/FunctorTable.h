//
//  FunctorTable.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/13/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#pragma once

#include "../stdafx.h"
#include "types.h"

using namespace std;

//
//  The funtor table is responable for 
//      1) Assigning each (functor name, arity) pair a unique integer Id
//      2) Maintaining a bi-directional map between these pairs and the Id's 
//      3) Storing the 'label' (put_structure) of the code for the functor
//
//  This is accomplished with
//      1) A map with a mangled string key (name + '*' + arity) to int (id)
//      2) A vector of 'Table Value' structs where the Id is the index 
//

class FunctorTable {
public:
    FunctorTable ();
    
    ~FunctorTable ();
    
    // Place (name, arity) in the table at label, of with nullptr for label
    // Will return the Id assigned to (name, arity)
    // If (name, arity) is already in the table with null label, label will be updated
    int addFunctor (string name, int arity, WAMword* labelPtr);
    
    // Returns Id if (name, arity) is in the table, else -1
    int getFunctorId (string name, int arity);

    string getName (int id);
    
    // Returns Id if (name, arity) is in the table, else -1
    int getArity (int id);

    // Returns label if (name, arity) is in the table, else nullptr
    WAMword* getLabel (int id);

    int getTableSize () { return m_Size; }
    
protected: 
    struct TableValue {
        int id;
        int arity;
        string name;
        WAMword* labelPtr;

        TableValue (int i, int a, string n, WAMword* l) {
            id = i;
            arity = a;
            name = n;
            labelPtr = l;
        }
   }; 
    
   int m_Size;

   vector <TableValue> m_ValueVector;

   unordered_map <string, int> m_StringMap;

   typedef unordered_map <string, int>::const_iterator MapElem;
};
