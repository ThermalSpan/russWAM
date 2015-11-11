//
//  Driver.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/6/2015
//  Copyright (c) 2015 Russell Wilhelm Bentley
//  Distributed under the MIT License
//

#include "Driver.h"

Driver::Driver (WAMword* code, FunctorTable* functorTable, StrVec* stringTable, int size) {
    m_Code = code;
    m_Preg = m_Code;
    m_CPreg = m_Code;
    m_size = size;
	m_FunctorTable = functorTable;
	m_StringTable = stringTable;
    
    m_wam = new WAMdebug (functorTable);
}   

Driver::~Driver () {
    delete (m_wam);
}

void Driver::run () {
    bool contExecution = true;
    RtnCode rtnCode;

    while (contExecution) {
        rtnCode = ExecuteInstruction (m_Preg);
 		if (rtnCode != SUCCESS) {
			contExecution = false;
		}		
    }
}

void Driver::incr () {
    m_Preg = m_Preg + 1;
}

RtnCode Driver::ExecuteInstruction (WAMword* instr) {
    RtnCode result;
    result = SUCCESS;

    switch (instr->op) {
        case OC_put_variable:
            m_wam->put_variable (instr->a, instr->b, instr->c);
            incr ();
            break;
        case OC_put_value:
            m_wam->put_value (instr->a, instr->b, instr->c);
            incr ();
            break;
        case OC_put_structure:
            m_wam->put_structure (instr->a, instr->b);
            incr ();
            break;
        case OC_set_variable:
            m_wam->set_variable (instr->a);
            incr ();
            break;
        case OC_set_value:
            m_wam->set_value (instr->a);
            incr ();
            break;
        case OC_get_variable:
            m_wam->get_variable (instr->a, instr->b, instr->c);
            incr ();
            break;
        case OC_get_value:
            m_wam->get_value (intr->a, instr->b, instr->c);
            incr ();
            break;
        case OC_get_structure:
            result = m_wam->get_structure (instr->a, instr->b);
            incr ();
            break;
        case OC_unify_variable:
            m_wam->unify_variable (instr->a);
            incr ();
            break;
        case OC_unify_value:
            m_wam->unify_value (instr->a);
            incr ();
            break;
        case OC_call:
            m_CPreg = m_Preg + 1;
            m_Preg = m_FunctorTable->getLabel (instr->a);
            break;
		case OC_write:
			cout << m_StringTable->at (instr->a) << endl;
            incr ();
			break;
		case OC_printHeap:
			m_wam->printHeap ();
            incr ();
			break;
		case OC_printArgRegisters:
            m_wam->printArgRegisters ();
            incr ();
			break;
		case OC_printResultArg:
            m_wam->printResultArg (instr->a);
            incr ();
			break;
        case OC_printHeapCell:
            m_wam->printHeapCell (instr->a);
            incr ();
            break;
        case OC_unifyHeapCells:
            m_wam->unifyHeapCells (instr->a, instr->b);
            incr ():
            break;
        case OC_proceed:
            m_Preg = m_CPreg;
		case OC_terminate:
			result = TERMINATED;
            break;       
        default:
            break;
    }
    
    return result;
}
