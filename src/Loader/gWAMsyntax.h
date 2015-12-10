//
//  gWAMsyntax.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 12/7/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#pragma once

#include <vector>
#include <unordered_map>
#include <iostream>
#include "../WAM/types.h"
#include "../WAM/FunctorTable.h"

using namespace std;

//
// Instruction Node
// The base for all types of instruction nodes. 
//
class InstrNode {
public:
    virtual bool isLabel ();
    virtual bool needsSwitchMap () { return false; }
    virtual bool passTwo (WAMword* word, FunctorTable &funcTable) = 0;
};

//
//  Predicate Node
//  Used in the syntax tree to store information related to predicates
//
class PredicateNode {
protected:
    vector <InstrNode*>* m_instrs;
    WAMword* m_codeArray;
    vector <WAMword*>* m_labels;
    unordered_map <int, int>* m_switchMap;
    string* m_name;
    int m_arity, m_functorId, m_instrCount;

public:
    PredicateNode (string* m_name, int arity, vector <InstrNode*>* m_instrs);
    // Used to gather all functor Names
    bool passOne (FunctorTable &funcTable);
    // Used to fill out the functor table.
    bool passTwo (FunctorTable &functorTable);
};

//
// Label Node
// The is used for labels.
//
class LabelNode {
protected:
   int m_label; 

public:
   LabelNode (int label) { m_label = label; }
   bool passTwo (WAMword* word, FunctorTable &funcTable)  { return false; }
   bool isLabel() { return true; };
   int getLabel() {return m_label; };
};

//
// Basic Instruction Node
// Used for any instruction that needs 0 or more integer arguments in WAM form.
//
class BasicInstrNode : public InstrNode {
protected:
   int m_a, m_b, m_c;
   OpCode m_op;

public:
   BasicInstrNode (OpCode op, int a = 0, int b = 0, int c = 0);
   bool passTwo (WAMword* word, FunctorTable &funcTable);
};

//
// Functor Instruction Node 
// Used for any instruction that has a functor with 0 or more integer arguments in WAM form.
//
class FunctorInstrNode : public InstrNode {
protected:
   int m_b, m_c;
   string* m_name;
   int m_arity;
   OpCode m_op;

public:
   FunctorInstrNode (OpCode op, string* name, int arity, int b = 0, int c = 0);
   bool passTwo (WAMword* word, FunctorTable &funcTable);
};

//
// Term Switch Node
// Used exclusivley for the switch_on_term instruction
//
class TermSwitchNode : public InstrNode {
protected:
   int m_var, m_atm, m_lst, m_str;

public:
   TermSwitchNode (int var, int atm, int lst, int str);
   bool passTwo (WAMword* word, FunctorTable &funcTable);
};

//
// Functor Label Pair
// Used to populate the hash map taking functors (atoms and structures) to their label
//
struct FunctorLabel {
    string* s_name;
    int s_arity;
    int s_label;
};

//
// Switch Map Node
// Used for switch_on_atom and switch_on_structure instructions
//
class SwitchMapNode : public InstrNode {
protected:
    vector <FunctorLabel>* m_pairs;
    OpCode m_op;

public:
   SwitchMapNode (OpCode op, vector <FunctorLabel>* atoms);
   bool needsSwitchMap() { return true; }
   bool setupSwitchMap(unordered_map <int, int>* switchMap, FunctorTable &functorTable);
   bool passTwo (WAMword* word, FunctorTable &funcTable);
};

// 
// Not-Used Node
// There are several gWAM instruction that are unsupported. This Node is for them.
//
class NotUsedNode : public InstrNode {
protected:
    string m_opName;
public:
   NotUsedNode (string opName);
   bool passTwo (WAMword* word, FunctorTable &funcTable);
};
