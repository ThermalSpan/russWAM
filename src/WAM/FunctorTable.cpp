//
//  FunctorTable.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/13/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "FunctorTable.h"

using namespace std;

FunctorTable::FunctorTable () {
    m_nextFunctorId = 0;   
}

FunctorTable::~FunctorTable () {
    for (auto it = m_ValueVector.begin(); it < m_ValueVector.end(); it++) {
        delete ((*it).s_labels);
        free ((*it).s_codeArray);
        if ((*it).s_labels != nullptr) {
            delete ((*it).s_labels);
        }
        if ((*it).s_switchMap != nullptr) {
            delete ((*it).s_switchMap);
        }
    }
}

string FunctorTable::mangleString (string* name, int arity) {
    string result =  *name + "*" + to_string (arity);
    return result;
}

int FunctorTable::addFunctor (string *name, int arity) {
    string key = mangleString (name, arity);
    auto element = m_StringMap.find (key);
    int result = -1;
    
    // If the (name, arity) is not in the functor table, add it
    if (element == m_StringMap.end ()) {
        result = m_nextFunctorId++;
		m_StringMap.emplace (key, result);
        m_ValueVector.push_back (TableValue (result, arity, name));
    }
    // Else, the functor is already in the table and we have a problem

    return result;
}

int FunctorTable::getFunctorId (string *name, int arity) {
    string key = mangleString (name, arity);
    auto element = m_StringMap.find (key);
    int result = -1;
    
    // If the functor is in the map we return its id    
    if (element != m_StringMap.end ()) {
       result = element->second;
    }
    // Else, return -1, which means there's a problem.

    return result;
}

void FunctorTable::setupFunctor (int functorId, WAMword* codeArray, vector <WAMword*> *labels, unordered_map <int, int>* switchMap) {
    assert (functorId >= 0 && functorId < m_nextFunctorId);
    TableValue val = m_ValueVector[functorId];
    val.s_codeArray = codeArray;
    val.s_labels = labels;
    val.s_switchMap = switchMap;
}

string *FunctorTable::getName (int functorId) {
    assert (functorId > 0 && functorId < m_nextFunctorId);   
    return m_ValueVector[functorId].s_name;
}

int FunctorTable::getArity (int functorId) {
    assert (functorId > 0 && functorId < m_nextFunctorId);
    return m_ValueVector[functorId].s_arity;
}

WAMword* FunctorTable::getLabel (int functorId, int labelNum) {
    assert (functorId > 0 && functorId < m_nextFunctorId);
    assert (labelNum < m_ValueVector[functorId].s_labels->size ());
    return m_ValueVector[functorId].s_labels->at (labelNum);
}

string FunctorTable::toString (int functorId) {
    return *getName (functorId) + "/" + getArity (functorId);
}
