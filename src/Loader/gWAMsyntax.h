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
#include <list>
#include <unordered_map>
#include <iostream>
#include "../WAM/types.h"
#include "../WAM/FunctorTable.h"

using namespace std;

//
// Register
// gWAM code encodes registers as x(n) or y(n), hence this struct
//
struct Reg {
    int s_regId;
    RegType s_type;

    Reg (int regId, RegType type) {
        s_regId = regId;
        s_type = type;
    }
};

//
// Functor
// In gWAM, a functor is identified with 'name'/'arity', hence this struct
//
struct Functor {
    string* s_name;
    int s_arity;

    Functor (string* name, int arity) {
        s_name = name;
        s_arity = arity;
    }
};

//
// Functor Label Pair
// Used to populate the hash map taking functors (atoms and structures) to their label
//
struct FunctorLabel {
    string* s_name;
    int s_arity;
    int s_label;

    FunctorLabel (string* name, int arity, int label) {
        s_name = name;
        s_arity = arity;
        s_label = label;
    }

    FunctorLabel (Functor* functor, int label) {
        s_name = functor->s_name;
        s_arity = functor->s_arity;
        s_label = label;
        cout << "functor label, deleting functor" << endl;
        delete (functor);
    }
};

//
// Instruction Node
// The base for all types of instruction nodes.
//
class InstrNode {
public:
    virtual ~InstrNode () {}
    virtual bool isLabel () {
        return false;
    }
    virtual bool needsSwitchMap () {
        return false;
    }
    virtual bool passTwo (WAMword* word, FunctorTable& functorTable) = 0;
};

//
//  Predicate Node
//  Used in the syntax tree to store information related to predicates
//
class PredicateNode {
protected:
    list <InstrNode*>* m_instrs;
    WAMword* m_codeArray;
    vector <WAMword*>* m_labels;
    unordered_map <int, int>* m_switchMap;
    Functor* m_functor;
    int m_functorId, m_instrCount;

public:
    PredicateNode (Functor* funtor, list <InstrNode*>* m_instrs);
    ~PredicateNode () {}
    // Used to gather all functor Names
    bool passOne (FunctorTable& functorTable);
    // Used to fill out the functor table.
    bool passTwo (FunctorTable& functorTable);

    string* getName () {
        return  m_functor->s_name;
    }
};

//
// Label Node
// The is used for labels.
//
class LabelNode : public InstrNode {
protected:
    int m_label;

public:
    LabelNode (int label) {
        m_label = label;
    }
    ~LabelNode () {}
    bool passTwo (WAMword* word, FunctorTable& functorTable)  {
        return false;
    }
    bool isLabel() {
        return true;
    };
    int getLabel() {
        return m_label;
    };
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
    ~BasicInstrNode () {}
    bool passTwo (WAMword* word, FunctorTable& functorTable);
};

//
// Register Instruction Node
// Used for any instruction that specifies a register type
//
class RegInstrNode : public InstrNode {
protected:
    Reg* m_reg;
    int m_b, m_c;
    OpCode m_op;

public:
    RegInstrNode (OpCode op, Reg* reg, int b = 0, int c = 0);
    ~RegInstrNode () {}
    bool passTwo (WAMword* word, FunctorTable& functorTable);
};

//
// Functor Instruction Node
// Used for any instruction that has a functor with 0 or more integer arguments in WAM form.
//
class FunctorInstrNode : public InstrNode {
protected:
    int m_b, m_c;
    Functor* m_functor;
    OpCode m_op;

public:
    FunctorInstrNode (OpCode op, Functor* m_functor, int b = 0, int c = 0);
    ~FunctorInstrNode () {}
    bool passTwo (WAMword* word, FunctorTable& functorTable);
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
    ~TermSwitchNode () {}
    bool passTwo (WAMword* word, FunctorTable& functorTable);
};

//
// Switch Map Node
// Used for switch_on_atom and switch_on_structure instructions
//
class SwitchMapNode : public InstrNode {
protected:
    list <FunctorLabel*>* m_pairs;
    OpCode m_op;

public:
    SwitchMapNode (OpCode op, list <FunctorLabel*>* atoms);
    ~SwitchMapNode () {}
    bool needsSwitchMap() {
        return true;
    }
    bool setupSwitchMap (unordered_map <int, int>* switchMap, FunctorTable& functorTable);
    bool passTwo (WAMword* word, FunctorTable& functorTable);
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
    ~NotUsedNode () {}
    bool passTwo (WAMword* word, FunctorTable& functorTable);
};
