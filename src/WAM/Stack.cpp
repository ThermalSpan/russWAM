//
//  Stack.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/1/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "Stack.h"

using namespace std;

Stack::Stack (int size) {
    m_array = (DataCell*) malloc (size * sizeof (DataCell));
    m_size = size;
    m_SP = 0;    
}

Stack::~Stack () {
    free (m_array);
}

DataCell* peek () {
    return &m_array[m_SP];
}

void push (DataCell* cell) {
    m_SP++;

    if (m_SP >= m_size) {
        cout << "Stack Overflow: " << m_SP << " out of " << m_size << endl;
    }    

    m_array[m_SP] = *cell;
}

void pop () {
    m_SP -= 1;
}

bool isEmpty () {
    return m_SP == 0;
}
