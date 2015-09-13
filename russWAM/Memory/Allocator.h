//
//  Allocator.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/12/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#pragma once

#include "stdafx.h"

class Allocator {

public:
  Allocator (size_t size) {
    m_size    = size;
    m_memused = 0;
  }

  ~Allocator () {}

  virtual void* allocate (const size_t size, const size_t alignment = 4) = 0;

  virtual void deallocate (void *pointer) = 0;

  void* pointerAdd (void* pointer, size_t offset) {
    return static_cast <void *> (static_cast <char *> (pointer) + offset);
  }

  void* getStart () {
    return m_start;
  }

  void* getEnd () {
    return pointerAdd (m_start, m_size);
  }

  size_t getSize () {
    return m_size;
  }

  size_t getMemUsed () {
    return m_memused;
  }

protected:
  size_t m_size;
  size_t m_memused;
  void*  m_start;
};

