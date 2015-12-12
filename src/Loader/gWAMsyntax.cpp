//
//  gWAMsyntax.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 12/7/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "gWAMsyntax.h"
#include <memory>

using namespace std;

PredicateNode::PredicateNode (Functor* functor, list <InstrNode*>* instrs) {
    m_functor = functor;
    m_instrs = instrs;
}

bool PredicateNode::passOne (FunctorTable &functorTable) {
    bool result;
    string* name = m_functor->s_name;
    int arity = m_functor->s_arity;

    int id = functorTable.addFunctor (name, arity);
    if (id == -1) {
        result = false;
        cout << "Parse Error: " << *name << "/" << arity << " is already in table.";
        cout << endl;
    } else {
        result = true;
        m_functorId = id;
    } 

    // Note that the +1 is for the null instruction at the end
    m_instrCount = m_instrs->size() + 1;
    for (auto it = m_instrs->begin (); it != m_instrs->end(); it++) {
       if ((*it)->isLabel ()) {
            m_instrCount -= 1;
       } 
    }

    return result;
}

bool PredicateNode::passTwo (FunctorTable &functorTable) {
    bool result = true;

    m_codeArray = (WAMword*) malloc (m_instrCount * sizeof(WAMword));
    m_labels = new vector <WAMword*> ();
    WAMword* nextWord = m_codeArray;

    // Push label 0 on to label vector
    m_labels->push_back (m_codeArray);
    // Not strictly necassary, but for assurance
    int nextLabel = 1;
    // Here build up the code array and supporting structures
    cout << "^ has " << m_instrs->size() << endl;
    for (auto it = m_instrs->begin(); it != m_instrs->end(); it++) {
        // Switch Map instructions need to setup their part of the map
        if ((*it)->needsSwitchMap ()) {
            if (m_switchMap == nullptr) {
                m_switchMap = new unordered_map <int, int> ();
            }
            result = result && dynamic_cast <SwitchMapNode*> (*it) ->setupSwitchMap (m_switchMap, functorTable);
        } 
        
        // Labels get special treatment 
        if ((*it)->isLabel ()) {
            int label = dynamic_cast <LabelNode*> (*it)->getLabel();
            if (label != nextLabel) {
                cout << "Parse Error: Incorrect Label Num " << label;
                cout << endl;
                result = false;  
            } else {
                nextLabel += 1;
                m_labels->push_back (nextWord);
            }
        } 
        // All other instructions are treated the same
        else {
            result = result && (*it)->passTwo (nextWord, functorTable);
            nextWord++;
        }

        delete (*it);
    }
    
    // Add Null word
    nextWord->op = OC_NULL;
    // Pass all the information to the functor table
    functorTable.setupFunctor (m_functorId, m_codeArray, m_labels, m_switchMap); 

    if (!result) {
        cout << "Parse Error: ^ Occured in " << functorTable.toString (m_functorId);
        cout << endl;
    }

    delete (m_functor);
    delete (m_instrs);    
    return result;
}

BasicInstrNode::BasicInstrNode (OpCode op, int a, int b, int c) {
    m_op = op;
    m_a = a;
    m_b = b;
    m_c = c;
}

RegInstrNode::RegInstrNode (OpCode op, Reg* reg, int b, int c) {
    m_op = op;
    m_reg = reg;
    m_b = b;
    m_c = c;
}

bool RegInstrNode::passTwo (WAMword* word, FunctorTable &functorTable) {
    word->a = m_reg->s_regId;
    word->b = m_b; 
    word->c = m_c;
    word->regType = m_reg->s_type;
    return true;
}

bool BasicInstrNode::passTwo (WAMword* word, FunctorTable &functorTable) {
    word->op = m_op;
    word->a = m_a;
    word->b = m_b;
    word->c = m_c;
    return true;
}

FunctorInstrNode::FunctorInstrNode (OpCode op, Functor* functor, int b, int c) {
    m_op = op;
    m_functor = functor;
    m_b = b;
    m_c = c;
}

bool FunctorInstrNode::passTwo (WAMword* word, FunctorTable &functorTable) {
    bool result = true;
    int functorId = 0; 
    int arity = m_functor->s_arity;
    string* name = m_functor->s_name;

    // For atoms (constants) we may or may not have seen them before.  
    if (arity == 0) {
        functorId = functorTable.getFunctorId (name, arity);
        if (functorId == -1) {
            // Haven't seen it? no problem, lets add it
            functorId = functorTable.addFunctor (name, arity);
        } else {
            delete (name);
        }
    } 
    // All other functors need to have been seen in passOne. 
    else {
        functorId = functorTable.getFunctorId (name, arity);
        if (functorId == -1) {
            result = false;
            cout << "Parse Error: " << *name << "/" << arity;
            cout << " is undefined" << endl;
        }
        delete (name);
    } 
   
    word->op = m_op; 
    word->a = functorId;
    word->b = m_b;
    word->c = m_c;

    delete (m_functor);
    return result;
}

TermSwitchNode::TermSwitchNode (int var, int atm, int lst, int str) {
    m_var = var;
    m_atm = atm;
    m_lst = lst;
    m_str = str;  
}

bool TermSwitchNode::passTwo (WAMword* word, FunctorTable &functorTable) {
    word->op = OC_switch_on_term;
    word->a = m_var;
    word->b = m_atm;
    word->c = m_lst;
    word->d = m_str; 
    return true;
}

SwitchMapNode::SwitchMapNode (OpCode op, list <FunctorLabel*>* pairs) {
    m_op = op;
    m_pairs = pairs; 
}

bool SwitchMapNode::setupSwitchMap (unordered_map <int, int>* switchMap, FunctorTable &functorTable) {
    bool result = true; 
     
    for (auto it = m_pairs->begin (); it != m_pairs->begin (); it++) {
       int functorId;
       int arity = (*it)->s_arity;
       string* name = (*it)->s_name;

       // For atoms (constants) we may or may not have seen them before.  
       if (arity == 0) {
            functorId = functorTable.getFunctorId (name, arity);
            if (functorId == -1) {
                // Haven't seen it? no problem, lets add it
                functorId = functorTable.addFunctor (name, arity);
            }
        } 
        // All other functors need to have been seen in passOne. 
        else {
            functorId = functorTable.getFunctorId (name, arity);
            if (functorId == -1) {
                result = false;
                cout << "Parse Error: Struct " << *name << "/" << arity;
                cout << " is undefined." << endl;
                continue;
            }
        }

       switchMap->emplace (functorId, (*it)->s_label);
       delete (name);
       delete (*it);
    }
    
    delete (m_pairs);
    return result;
}

bool SwitchMapNode::passTwo (WAMword* word, FunctorTable &functorTable) {
    word->op = m_op;
    return true;
}

NotUsedNode::NotUsedNode (string opName) {
    m_opName = opName;
}

bool NotUsedNode::passTwo (WAMword* word, FunctorTable &functorTable) {
    cout << "Parse Error: " << m_opName << " is not a supported WAM operation. Sorry.";
    cout << endl; 
    return false;
}



