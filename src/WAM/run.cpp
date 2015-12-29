//
//  run.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 12/14/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley
//  Distributed under the MIT License
//

#include "WAM.h"
#include <iostream>

using namespace std;

bool WAM::run (string* functor, int arity) {
    bool result = true;
    int queryId = m_functorTable->getFunctorId (functor, arity);

    if (queryId == -1) {
        panic ("ERROR: query not found...");
    }

    m_P = m_functorTable->getLabel (queryId, 0);

    int icount = 0;
    while (m_P->op != OC_NULL && icount < 20) {
        executeInstr (m_P);
    }

    return result;
}

bool WAM::runBacktrack () {
    bool result = true;
	cout << "run backtrack " << endl;
    if (m_B != nullptr) {
        m_P = m_B->L;
        while (m_P->op != OC_NULL) {
            executeInstr (m_P);
        }
    } else {
        result = false;
    }

    return result;
}

bool WAM::executeInstr (WAMword* word) {
    switch (word->op) {
    case OC_put_variable:
        put_variable (word->regType, word->a, word->b);
        break;
    case OC_put_value:
        put_value (word->regType, word->a, word->b);
        break;
    case OC_put_unsafe_value:
        put_unsafe_value (word->a, word->b);
        break;
    case OC_put_structure:
        put_structure (word->a, word->b);
        break;
    case OC_put_list:
        put_list (word->a);
        break;
    case OC_put_void:
        put_void (word->a);
        break;
    case OC_put_constant:
        put_constant (word->a, word->b);
        break;
    case OC_set_variable:
        set_variable (word->regType, word->a);
        break;
    case OC_set_value:
        set_value (word->regType, word->a);
        break;
    case OC_set_local_value:
        set_local_value (word->regType, word->a);
        break;
    case OC_set_constant:
        set_constant (word->a);
        break;
    case OC_set_void:
        set_void (word->a);
        break;
    case OC_allocate:
        allocate (word->a);
        break;
    case OC_deallocate:
        deallocate ();
        break;
    case OC_call:
        call (word->a);
        break;
    case OC_execute:
        execute (word->a);
        break;
    case OC_proceed:
        proceed ();
        break;
    case OC_fail:
        //TODO: We need to figure out fail ()?
        //fail ();
        panic ("ERROR: We have not defined fail yet" );
        break;
    case OC_switch_on_term:
        switch_on_term (word->a, word->b, word->c, word->d);
        break;
    case OC_switch_on_constant:
        switch_on_constant ();
        break;
    case OC_switch_on_structure:
        switch_on_structure ();
        break;
    case OC_get_variable:
        get_variable (word->regType, word->a, word->b);
        break;
    case OC_get_value:
        get_value (word->regType, word->a, word->b);
        break;
    case OC_get_structure:
        get_structure (word->a, word->b);
        break;
    case OC_get_list:
        get_list (word->a);
        break;
    case OC_get_constant:
        get_constant (word->a, word->b);
        break;
    case OC_get_void:
        // TODO: we need a get void...
        //get_void ();
        panic ("ERROR: We have not yet defined get_void...");
        break;
    case OC_unify_variable:
        unify_variable (word->regType, word->a);
        break;
    case OC_unify_value:
        unify_value (word->regType, word->a);
        break;
    case OC_unify_local_value:
        unify_local_value (word->regType, word->a);
        break;
    case OC_unify_constant:
        unify_constant (word->a);
        break;
    case OC_unify_list:
        // TODO: we need a unify_list...
        panic ("ERROR: We have not yet defined unify_list");
        break;
    case OC_unify_void:
        unify_void (word->a);
        break;
    case OC_unify_structure:
        // TODO: we need a unify_structure
        //unify_structure ();
        panic ("ERRORL We have not yet defined unify_structure");
        break;
    case OC_try_me_else:
        try_me_else (word->a);
        break;
    case OC_retry_me_else:
        retry_me_else (word->a);
        break;
    case OC_trust_me_else_fail:
        trust_me_else_fail ();
        break;
    case OC_try:
        try_ (word->a);
        break;
    case OC_retry:
        retry (word->a);
        break;
    case OC_trust:
        trust (word->a);
        break;
    case OC_neck_cut:
        neck_cut ();
        break;
    case OC_get_level:
        get_level (word->a);
        break;
    case OC_cut:
        cut (word->a);
        break;
    case OC_terminate:
        terminate ();
        break;
    case OC_NULL:
        cout << "Error: How did an OC_NULL word get into the executeInstr function?" << endl;
        break;
    case OC_FAIL:
        cout << "Backtracking fail. In other words, NO." << endl;
        delete (m_P);
        break;
    }

    return true;
}

