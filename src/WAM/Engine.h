//
//  Engine.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/12/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#pragma once

#include "../stdafx.h"
#include "types.h"

#define ARG_REG_COUNT 10

class WAM {
public:
  WAM ();
  
  ~WAM ();

protected:

  ValueCell* ArgRegisters;

};


