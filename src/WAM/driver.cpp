//
//  driver.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/6/2015
//  Copyright (c) 2015 Russell Wilhelm Bentley
//  Distributed under the MIT License
//

#include "WAM.h"

void WAM::run () {
    bool contExecution = true;
    RtnCode rtnCode;

    while (contExecution) {
        rtnCode = ExecuteInstruction (m_Preg);
 		if (rtnCode != SUCCESS) {
			contExecution = false;
		}		
    }
}

void WAM::incrPreg () {
    m_Preg = m_Preg + 1;
}

RtnCode WAM::ExecuteInstruction (WAMword* instr) {
    RtnCode result;
    result = SUCCESS;

    switch (instr->op) {
        case OC_put_variable:
            put_variable (instr->a, instr->b, instr->c);
            break;
        case OC_put_value:
            put_value (instr->a, instr->b);
            break;
        case OC_put_structure:
            put_structure (instr->a, instr->b);
            break;
        case OC_set_variable:
            set_variable (instr->a);
            break;
        case OC_set_value:
            set_value (instr->a);
            break;
        case OC_get_variable:
            get_variable (instr->a, instr->b, instr->c);
            break;
        case OC_get_value:
            get_value (instr->a, instr->b, instr->c);
            break;
        case OC_get_structure:
            result = get_structure (instr->a, instr->b);
            break;
        case OC_unify_variable:
            unify_variable (instr->a);
            break;
        case OC_unify_value:
            unify_value (instr->a);
            break;
        case OC_call:
            m_Preg = m_FunctorTable->getLabel (instr->a);
            break;
		case OC_write:
			cout << m_StringTable->at (instr->a) << endl;
			break;
		case OC_printHeap:
			printHeap ();
			break;
		case OC_printArgRegisters:
            printArgRegisters ();
			break;
		case OC_printResultArg:
            printResultArg (instr->a);
			break;
        case OC_printHeapCell:
            printHeapCell (instr->a);
            break;
        case OC_unifyHeapCells:
            unifyHeapCells (instr->a, instr->b);
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
