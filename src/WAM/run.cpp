// 
//  run.cpp
//  russWAM 
//
//  Created by Russell Wilhelm Bentley on 12/14/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley
//  Distributed under the MIT License
//

#include "WAM.h"

bool run (string functor, int arity) {
    bool result = true;
    int queryId = m_functorTable.getLabel (functor, arity);
    m_P = m_functorTable.getLabel (queryId, 0);

    while (m_P->op != OC_NULL) {
        
    }

    return result;
}

bool executeInstr (WAMword* word) {
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
            put_void ();
            break;
        case OC_put_constant:
            put_constant (word->a, word->b);
            break;
        case OC_set_variable:
            set_variable (word->regType, word-->a);
            break;
        case OC_set_value:
            set_value (word->regType, word->a);
            break;
        case OC_set_localvalue:
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
            fail ();
            break;
        case OC_switch_on_term:
            switch_on_term ();
            break;
        case OC_switch_on_constant:
            switch_on_constant ();
            break;
        case OC_switch_on_structure:
            switch_on_structure ();
            break;
        case OC_get_variable:
            get_variable ();
            break;
        case OC_get_value:
            get_value ();
            break;
        case OC_get_structure:
            get_structure ();
            break;
        case OC_get_list:
            get_list ();
            break;
        case OC_get_constant:
            get_constant ();
            break;
        case OC_get_void:
            get_void ();
            break;
        case OC_unify_variable:
            unify_variable ();
            break;
        case OC_unify_value:
            unify_value ();
            break;
        case OC_unify_local_value:
            unify_local_value ();
            break;
        case OC_unify_constant:
            unify_constant ();
            break;
        case OC_unify_list:
            unify_list ();
            break;
        case OC_unify_void:
            unify_void ();
            break;
        case OC_unify_structure:
            unify_structure ();
            break;
        case OC_try_me_else:
            try_me_else ();
            break;
        case OC_retry_me_else:
            retry_me_else ();
            break;
        case OC_trust_me:
            trust_me ();
            break;
        case OC_trust_me_else_fail:
            trust_me_else_fail ();
            break;
        case OC_try:
            try ();
            break;
        case OC_retry:
            retry ();
            break;
        case OC_trust:
            trust ();
            break;
        case OC_neck_cut:
            neck_cut ();
            break;
        case OC_get_level:
            get_level ();
            break;
        case OC_cut:
            cut ();
            break;
        case OC_terminate:
            terminate ();
            break;
        case OC_NULL:
            cout << "Error: How did an OC_NULL word get into the executeInstr function?" << endl;
            break;
    }
}

