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

class FunctorTable {
public:
    FunctorTable ();
    
    ~FunctorTable ();

    int addFunction (int arity, string name, WAMword* labelPtr);

    string getName (int id);

    int getArity (int id);

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
};
