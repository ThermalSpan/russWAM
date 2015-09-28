//
//  PoolAllocator.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/23/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#pragma once

#include "Allocator.h"

class PoolAllocator : public Allocator {

public:
    PoolAllocator (size_t size, size_t objectSize, size_t alignment);

    ~PoolAllocator ();

    size_t getObjectSize () { return m_objectSize; }

    void* allocate (size_t size, size_t alignment);

    void deallocate (void* pointer);

    void* allocate (int n);

protected:
    size_t m_objectSize;
    size_t m_alignment;

    void** m_freeList;
};
