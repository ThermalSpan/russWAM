//
//  Driver.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/6/2015
//  Copyright (c) 2015 Russell Wilhelm Bentley
//  Distributed under the MIT License
//

#include "Driver.h"

Driver::Driver (WamWord* code, WamWord* start, int size) : m_wam () {
    m_Code = code;
    m_Preg = start;
    m_size = size;
    
    m_wam = new WAM ();
}   

Driver::Driver () {
    delete (m_wam);
}

void Driver::run () {
    bool contExecution = true;
    RtnCode rtnCode;

    while (contExecution) {
        rtnCode = ExecuteInstruction (m_Preg);
        m_Preg = &m_Preg[1];
    }
}

RtnCode ExecuteInstruction (WamWord* inst) {
    RtnCode result;
    result = SUCCESS;

    switch (inst->op) {
        case PUT_STRUCTURE:
            m_wam->put_structure (inst->a1, inst->a2, inst->a3);
            break;
        case SET_VARIABLE:
            m_wam->set_variable (inst->a1);
            break;
        case SET_VALUE:
            m_wam->set_value (inst->a1);
            break;
        case GET_STRUCTURE:
            result = m_wam->get_structure (ints->a1, inst->a2, inst->a3);
            break;
        case UNIFY_VARIABLE:
            m_wam->unify_variable (inst->a1);
            break;
        case UNIFY_VALUE:
            m_wam->unify_value (inst->a1);
            break;
        case CALL:
            
            break;
        case PROCEED:

            break;       
        case default:
            break;
    }
    
    return result;
}
