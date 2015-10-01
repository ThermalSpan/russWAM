//
//  Stack.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/1/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#pragma once

#include "../stdafx.h"
#include "types.h"

class Stack {
public: 
    Stack (int size);

    ~Stack ();

    DataCell* peek ();
    
    void push (DataCell* cell);

    void pop ();

    bool isEmpty ();

protected:
    int m_size;

    int m_SP;

    DataCell* m_array;
};
