//
//  main.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/12/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "stdafx.h"
#include "WAM/WAMdebug.h"
#include "Loader/rWAMparser.h"

using namespace std;

int main(int argc, const char * argv[]) {
	const char* fn = 0;
   	if (argc == 2)
      	fn = argv[1];
   	rWAMparser p;
   	p.run(fn);

   	if (p.status ()) {
     	cout << "Input OK" << endl;
   	} else 
     	cout << "Input BAD" << endl;
    return 0;
}
