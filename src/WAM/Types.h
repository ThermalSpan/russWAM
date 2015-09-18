//
//  Types.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/15/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//  

#pragma once

#include "../stdafx.h"

enum Tag {REF, STR};

struct ValueCell {
  Tag tag;
  ValueCell* ref;
};

struct FunctorCell {
  int functorId;
  size_t n;
};

enum CellType {VAL, FUN};

union testCell {
  FunctorCell fc;
  ValueCell vc;
};

struct DataCell {
  CellType type;

  testCell t;
};

struct testCell2 {
  int a;
  int b;

  union u {
	ValueCell vc;
	FunctorCell fc;
  };
};


