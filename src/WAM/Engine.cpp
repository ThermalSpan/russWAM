//
//  Engine.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/12/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include "Engine.h"

WAM::WAM () {
  ArgRegisters = (ValueCell*) malloc (ARG_REG_COUNT * sizeof (ValueCell));
}

WAM::~WAM () {
  free (ArgRegisters);
}
