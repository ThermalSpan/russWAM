//
//  PoolAllocator.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/23/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include "PoolAllocator.h"

PoolAllocator::PoolAllocator (size_t size, size_t objectSize, size_t alignment) : Allocator (size) {
    m_start = malloc (size);
    m_freeList = (void**)m_start;
    m_objectSize = objectSize;
    
    void** pointer = m_freeList;
    for(size_t i = 0; i < m_size; i += objectSize) {
        *pointer = pointerAdd (pointer, objectSize);
        pointer = (void**) *pointer;
    }

    *pointer = nullptr;
}

PoolAllocator::~PoolAllocator () {
    free (m_start);
}

void* PoolAllocator::allocate (size_t size, size_t alignment) {
    /*if (m_freeList == nullptr) {
        return nullptr;
    }

    void *result = m_freeList;

    m_freeList = (void**) *m_freeList;

    m_memused += m_objectSize;
    m_memleft -= m_objectSize;
    m_allocations++;

    return result;*/

    return nullptr;
}

void* PoolAllocator::allocate (int n) {
   if (pointerAdd(m_freeList, n) == nullptr) {
        return nullptr;
   }

   void *result = m_freeList;
   //m_freeList = (void**) *pointerAdd (m_freeList,n);

   m_memused += n * m_objectSize;
   m_memleft -= n * m_objectSize;
   m_allocations++;

   return result;
}

void PoolAllocator::deallocate (void* pointer) {
    *( (void**) pointer) = m_freeList;
    //m_freeList = (void**) pointer;

    m_memused -= m_objectSize;
    m_memleft += m_objectSize;
}
