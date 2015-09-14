//
//  StackAllocator.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/12/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include "StackAllocator.h"

StackAllocator::StackAllocator (size_t size) : Allocator (size) {
  m_start = malloc (m_size);
}

StackAllocator::~StackAllocator () {

}

void* StackAllocator::allocate (size_t size, size_t alignment) {

}

void StackAllocator::deallocate (void *pointer) {

}

