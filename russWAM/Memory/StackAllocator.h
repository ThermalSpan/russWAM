//
//  StackAllocator.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/12/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#pragma once

#include "stdafx.h"
#include "Allocator.h"

class StackAllocator : public Allocator {

public:
  StackAllocator (size_t size) : Allocator (size);

  ~StackAllocator ();

  void* allocate (size_t size, size_t alignment = 4);

  void deallocate (void *pointer);

protected:
  void* m_stackpointer;
};
