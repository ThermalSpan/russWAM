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
	   	m_Preg = &m_Preg[1];
    }
}

RtnCode Driver::ExecuteInstruction (WAMword* instr) {
    RtnCode result;
    result = SUCCESS;

    switch (instr->op) {
        case OC_put_structure:
            cout << "driver: put_structure " << endl;
            m_wam->put_structure (instr->a, instr->b);
            break;
        case OC_set_variable:
            m_wam->set_variable (instr->a);
            break;
        case OC_set_value:
            cout << "driver: set_value " << instr->a << endl;
            m_wam->set_value (instr->a);
            break;
        case OC_get_structure:
            cout << "driver: get_structure" << instr->a << " " << instr->b << endl;
            result = m_wam->get_structure (instr->a, instr->b);
            break;
        case OC_unify_variable:
            m_wam->unify_variable (instr->a);
            break;
        case OC_unify_value:
            m_wam->unify_value (instr->a);
            break;
        case OC_call:
            break;
		case OC_write:
			cout << m_StringTable->at (instr->a) << endl;
			break;
		case OC_printHeap:
			m_wam->printHeap ();
			break;
		case OC_printArgRegisters:
            m_wam->printArgRegisters ();
			break;
		case OC_printResultArg:
            m_wam->printResultArg (instr->a);
			break;
		case OC_terminate:
			result = TERMINATED;
            break;       
        default:
            break;
    }
    
    return result;
}
