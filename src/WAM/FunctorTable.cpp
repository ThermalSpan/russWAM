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
    m_Size = 0;   
}

FunctorTable::~FunctorTable () {

}

int FunctorTable::addFunction (int arity, string name, WAMword* labelPtr) {
    string key = name + "*" + to_string(arity);
    unordered_map <string, int>::const_iterator element = m_StringMap.find (key);
    int result;

    if (element == m_StringMap.end ()) {
        result = m_Size++;
        m_ValueVector.push_back (TableValue (result, arity, name, labelPtr));
    }
    else {
        result = element->second;   
    }

    return result;
}

string FunctorTable::getName (int id) {
    if (id < 0 || id >= m_Size) {
        return "?-ID NOT FOUND";
    } 
    else {
        return m_ValueVector[id].name;
    }
}

int FunctorTable::getArity (int id) {
    if (id < 0 || id >= m_Size) {
        return -1;
    }    
    else {
        return m_ValueVector[id].arity;
    } 
}

WAMword* FunctorTable::getLabel (int id) {
    if (id < 0 || id >= m_Size) {
        return nullptr;
    } 
    else {
        return m_ValueVector[id].labelPtr;
    } 
}
