//
//  main.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/12/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include <iostream>
#include "WAM/types.h"
using namespace std;

int main(int argc, const char * argv[]) {
  cout << "size value Cell" << sizeof(ValueCell) << endl;
  cout << "size FunctorCell" << sizeof(FunctorCell) << endl;
  return 0;
}
