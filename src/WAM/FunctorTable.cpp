//
//  FunctorTable.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/13/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "FunctorTable.h"
#include <iostream>

using namespace std;

FunctorTable::FunctorTable () {
    m_nextFunctorId = 0;   
}

FunctorTable::~FunctorTable () {
    for (auto it = m_ValueVector.begin(); it < m_ValueVector.end(); it++) {
        delete ((*it).s_name);

        if ((*it).s_codeArray != nullptr) {
            free ((*it).s_codeArray);
        }
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

void FunctorTable::setupFunctor (int functorId, WAMword* codeArray, vector <WAMword*>* labels, unordered_map <int, int>* switchMap) {
    assert (functorId >= 0 && functorId < m_nextFunctorId);
    m_ValueVector[functorId].s_codeArray = codeArray;
    m_ValueVector[functorId].s_labels = labels;
    m_ValueVector[functorId].s_switchMap = switchMap;
}

string *FunctorTable::getName (int functorId) {
    assert (functorId >= 0 && functorId < m_nextFunctorId);   
    return m_ValueVector[functorId].s_name;
}

int FunctorTable::getArity (int functorId) {
    assert (functorId >= 0 && functorId < m_nextFunctorId);
    return m_ValueVector[functorId].s_arity;
}

WAMword* FunctorTable::getLabel (int functorId, int labelNum) {
    assert (functorId >= 0 && functorId < m_nextFunctorId);
    assert (labelNum < m_ValueVector[functorId].s_labels->size ());
    return m_ValueVector[functorId].s_labels->at (labelNum);
}

string FunctorTable::toString (int functorId) {
    return *getName (functorId) + "/" + to_string (getArity (functorId));
}

void FunctorTable::debugPrint () {
    for (auto it = m_ValueVector.begin (); it != m_ValueVector.end (); it++) {
        cout << "------------------------------------------------------------" << endl; 
        cout << *((*it).s_name) << "/" << (*it).s_arity << " -> id: " << (*it).s_id << endl;    
        if ((*it).s_arity == 0) {
            cout << "ATOM" << endl;
        } else {
            WAMword* word = (*it).s_codeArray;
            int label = 0;
            while (word->op != OC_NULL) {
                cout << to_string (word->op) << endl;
                word++;
            }
        }
    }
}

string to_string (OpCode op) {
   switch (op) {
        case OC_put_variable:
            return "OC_put_variable";
            break;
        case OC_put_value:
            return "OC_put_value";
            break;
        case OC_put_unsafe_value:
            return "OC_put_unsafe_value";
            break;
        case OC_put_structure:
            return "OC_put_structure";
            break;
        case OC_put_list:
            return "OC_put_list";
            break;
        case OC_put_void:
            return "OC_put_void";
            break;
        case OC_put_constant:
            return "OC_put_constant";
            break;
        case OC_set_variable:
            return "OC_set_variable";
            break;
        case OC_set_value:
            return "OC_set_value";
            break;
        case OC_set_localvalue:
            return "OC_set_localvalue";
            break;
        case OC_set_constant:
            return "OC_set_constant";
            break;
        case OC_set_void:
            return "OC_set_void";
            break;
        case OC_allocate:
            return "OC_allocate";
            break;
        case OC_deallocate:
            return "OC_deallocate";
            break;
        case OC_call:
            return "OC_call";
            break;
        case OC_execute:
            return "OC_execute";
            break;
        case OC_proceed:
            return "OC_proceed";
            break;
        case OC_fail:
            return "OC_fail";
            break;
        case OC_switch_on_term:
            return "OC_switch_on_term";
            break;
        case OC_switch_on_constant:
            return "OC_switch_on_constant";
            break;
        case OC_switch_on_structure:
            return "OC_switch_on_structure";
            break;
        case OC_get_variable:
            return "OC_get_variable";
            break;
        case OC_get_value:
            return "OC_get_value";
            break;
        case OC_get_structure:
            return "OC_get_structure";
            break;
        case OC_get_list:
            return "OC_get_list";
            break;
        case OC_get_constant:
            return "OC_get_constant";
            break;
        case OC_get_void:
            return "OC_get_void";
            break;
        case OC_unify_variable:
            return "OC_unify_variable";
            break;
        case OC_unify_value:
            return "OC_unify_value";
            break;
        case OC_unify_local_value:
            return "OC_unify_local_value";
            break;
        case OC_unify_constant:
            return "OC_unify_constant";
            break;
        case OC_unify_list:
            return "OC_unify_list";
            break;
        case OC_unify_void:
            return "OC_unify_void";
            break;
        case OC_unify_structure:
            return "OC_unify_structure";
            break;
        case OC_try_me_else:
            return "OC_try_me_else";
            break;
        case OC_retry_me_else:
            return "OC_retry_me_else";
            break;
        case OC_trust_me:
            return "OC_trust_me";
            break;
        case OC_trust_me_else_fail:
            return "OC_trust_me_else_fail";
            break;
        case OC_try:
            return "OC_try";
            break;
        case OC_retry:
            return "OC_retry";
            break;
        case OC_trust:
            return "OC_trust";
            break;
        case OC_neck_cut:
            return "OC_neck_cut";
            break;
        case OC_get_level:
            return "OC_get_level";
            break;
        case OC_cut:
            return "OC_cut";
            break;
        case OC_terminate:
            return "OC_terminate";
            break;
        case OC_NULL:
            return "OC_NULL";
            break;
   }
}
