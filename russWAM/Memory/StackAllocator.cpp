//
//  StackAllocator.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/12/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include "StackAllocator.h"

StackAllocator::StackAllocator (size_t size) {
  m_start = malloc (m_size);
}

StackAllocator::~StackAllocator () {

}

void* StackAllocator::allocatei (*size_t size, size_t alignment = 4) {

}

void StackAllocator::deallocate (void *pointer) {

}

