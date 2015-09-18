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
  ArgRegisters = (DataCell*) malloc (ARG_REG_COUNT * sizeof (DataCell));
}

WAM::~WAM () {
  free (ArgRegisters);
}

void put_structure (int functorId, int arity, int regId) {

}

void set_variable (int regId) {

}

void set_value (int regId) {

}
