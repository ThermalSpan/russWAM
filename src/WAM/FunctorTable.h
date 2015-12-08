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

class FunctorTable {
protected:
    struct TableValue {
        int s_id;
        int s_arity;
        string* s_name;
        WAMword* s_codeArray;
        vector <WAMword*>* s_labels;

        TableValue (int id, int arity, string* name) {
            s_id = id;
            s_arity = arity;
            s_name = name;
        }
   }; 

   int m_nextFunctorId;

   vector <TableValue> m_ValueVector;

   unordered_map <string, int> m_StringMap;

   string mangleString (string *name, int arity);

public:

    FunctorTable ();
    
    ~FunctorTable ();
    
    int addFunctor (string *name, int arity);
    
    int getFunctorId (string *name, int arity);

    void setupFunctor (int functorId, WAMword* codeArray, vector <WAMword*> *labels);

    string *getName (int functorId);
    
    int getArity (int functorId);

    WAMword* getLabel (int functorId, int labelNum);

    int getTableSize () { return m_nextFunctorId; }
};
