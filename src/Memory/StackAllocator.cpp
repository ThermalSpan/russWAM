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
  // Check if there is enough space
  if (m_memleft < size + alignment) {
    return nullptr;
  }

  // Align stack pointer to get next spot
  void* result = m_stackpointer;
  std::align (alignment, size, result, m_memleft);

  // Update state
  m_memused    = m_size - m_memleft;
  m_stackpointer = pointerAdd (result, size);
 
  return result;
}

void StackAllocator::deallocate (void *pointer) {

}

size_t StackAllocator::getMemUsed () {
  return static_cast <char *> (m_stackpointer) - static_cast <char *> (m_start);
}


