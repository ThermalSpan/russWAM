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

int FunctorTable::addFunctor (string nameString, int arity, WAMword* labelPtr) {
    string key = nameString + "*" + to_string (arity);
    MapElem element = m_StringMap.find (key);
    int result;

    if (element == m_StringMap.end ()) {
        result = m_Size++;
		m_StringMap.emplace (key, result);
        m_ValueVector.push_back (TableValue (result, arity, nameString, labelPtr));
    }
    else {
        if (m_ValueVector.at(element->second).labelPtr == nullptr) {
            m_ValueVector.at(element->second).labelPtr = labelPtr;
        }
        result = element->second;   
    }

    return result;
}

int FunctorTable::getFunctorId (string nameString, int arity) {
    string key = nameString + "*" + to_string (arity);
    MapElem element = m_StringMap.find (key);
    int result = -1;

    if (element != m_StringMap.end ()) {
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
