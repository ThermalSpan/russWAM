//
//  FunctorTable.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/13/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#pragma once

#include <stdlib.h>
#include <assert.h>
#include <string>
#include <unordered_map>
#include "types.h"

using namespace std;

string to_string (OpCode op);

class FunctorTable {
protected:
    struct TableValue {
        int s_id;
        int s_arity;
        string* s_name;
        WAMword* s_codeArray;
        vector <WAMword*>* s_labels;
        unordered_map <int, int>* s_switchMap;

        TableValue (int id, int arity, string* name) {
            s_id = id;
            s_arity = arity;
            s_name = name;
            s_codeArray = nullptr;
            s_labels = nullptr;
            s_switchMap = nullptr;
        }
   }; 

   int m_nextFunctorId;

   vector <TableValue> m_ValueVector;

   unordered_map <string, int> m_StringMap;

   string mangleString (string *name, int arity);

public:

    FunctorTable ();
    
    ~FunctorTable ();
    // Returns the functor id, or -1 if already in the table
    int addFunctor (string *name, int arity);
    
    int getFunctorId (string *name, int arity);

    void setupFunctor (int functorId, WAMword* codeArray, vector <WAMword*>* labels, unordered_map <int, int>* switchMap = nullptr);

    string *getName (int functorId);
    
    int getArity (int functorId);

    WAMword* getLabel (int functorId, int labelNum);

    int getTableSize () { return m_nextFunctorId; }

    string toString (int functorId);

    void debugPrint ();
};
